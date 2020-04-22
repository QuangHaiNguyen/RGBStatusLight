
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "debug.h"
#include "led.h"

#define CLI_EN          0
#define WIFI_EN         0
#define TEST_WS2812     0
#define TEST_RTC        1

#if TEST_RTC
#include "atmega4808_rtc.h"
#endif

#if WIFI_EN
#include "mcc_generated_files/winc/m2m/m2m_wifi.h"
#include "mcc_generated_files/winc/m2m/m2m_types.h"
#include "common/winc_defines.h"
#include "driver/winc_adapter.h"
#endif

#if CLI_EN
#include "cli.h"
#endif 

#if TEST_WS2812
#include "WS2812.h"
#include "include/winc_legacy.h"
#endif


#if WIFI_EN
void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg);
#endif

#if TEST_WS2812
void Test_WS2812(void);
#endif

#if CLI_EN
static char ch;
void Test1(void);
void Test2(void);
void Test3(void);
CLI_Status cli_stt;
command_t cmd_table[3] = {
        {"test_1", Test1},
		{"test_2", Test2},
        {"test_3", Test3},
};

#endif


void UART2_RXCallback(void);
void SW1_InterruptHandler(void);
void SW0_InterruptHandler(void);

uint8_t version;
uint8_t sub_version;
uint8_t ssub_version;
Led_Comp led; 
bool flag = false;
/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    sei();
    PRINT_INFO("%s", "********************************************\n");
    PRINT_INFO("%s", "System initialized\n");
    USART2_SetISRCb(UART2_RXCallback, USART2_RX_CB);
    
#if CLI_EN
    CLI_Init(cmd_table, 3);
    CLI_GetVersion(&version, &sub_version, &ssub_version);
    PRINT_INFO("CLI version %02d.%02d.%02d\n", version, sub_version,ssub_version);
#endif
    
    LED_Init(&led);
    led.LED_GetVerion(&version, &sub_version, &ssub_version);
    PRINT_INFO("LED version %02d.%02d.%02d\n", version, sub_version,ssub_version);
    PRINT_INFO("number of available Led: %d\n", led.NumOfLed());
    
    PORTF_SW1_SetInterruptHandler(SW1_InterruptHandler);
    PORTF_SW0_SetInterruptHandler(SW0_InterruptHandler);
    
#if TEST_WS2812
    Test_WS2812();
#endif

#if TEST_RTC
    ATMEGA4808_RTC_Init();
    ATMEGA4808_RTC_Start();
#endif
    
#if WIFI_EN
    tstrWifiInitParam wifi_param;
    winc_adapter_init();
    wifi_param.pfAppWifiCb = Wifi_EventCallback;

    if(!m2m_wifi_init(&wifi_param)){
        
        tstrM2MAPConfig apConfig = {
            "WINC_SSID", // Access Point Name.
            1, // Channel to use.
            0, // Wep key index.
            WEP_40_KEY_STRING_SIZE, // Wep key size.
            "1234567890", // Wep key.
            M2M_WIFI_SEC_OPEN, // Security mode.
            SSID_MODE_VISIBLE, // SSID visible.
            {192, 168, 1, 1}
         };
        
        m2m_wifi_start_provision_mode(&apConfig, "atmelwincconfig.com", 1);
    }
    PRINT_DEBUG("%s", "AP Started\n");
#endif
    /* Replace with your application code */
    
    while (1){
#if WIFI_EN
        m2m_wifi_handle_events(NULL);
#endif
        
#if CLI_EN
        cli_stt = CLI_ProccessCommand();
        if(CLI_CMD_NOTFOUND == cli_stt){
            printf("command not found\r\n");
        }
#endif
    }
}

#if WIFI_EN
void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg)
{
    tstrM2MProvisionInfo *pstrProvInfo;
    switch(u8WiFiEvent){
        case M2M_WIFI_RESP_CON_STATE_CHANGED:
            {
                tstrM2mWifiStateChanged *pstrInfo = (tstrM2mWifiStateChanged*)pvMsg;
                switch(pstrInfo->u8CurrState){
                    case M2M_WIFI_CONNECTED:
                        PRINT_DEBUG("%s", "connected\n");
                        m2m_wifi_get_connection_info(); 
                    break;
                    case M2M_WIFI_DISCONNECTED:
                        PRINT_DEBUG("%s", "disconnected\n");
                        break;
                    case M2M_WIFI_ROAMED:
                        PRINT_DEBUG("%s", "roam to new AP\n");
                    break;
                    case M2M_WIFI_UNDEF:
                        PRINT_DEBUG("%s", "undefined state\n");
                    break;
                }
            }
            break;
        case M2M_WIFI_RESP_CONN_INFO:
            {
                tstrM2MConnInfo *pstrInfo = (tstrM2MConnInfo*)pvMsg;
                PRINT_DEBUG("Connected to: %s\n", pstrInfo->acSSID);
            }
            break;
        case M2M_WIFI_RESP_PROVISION_INFO:           
            pstrProvInfo = (tstrM2MProvisionInfo*)pvMsg;
            if(pstrProvInfo->u8Status == M2M_SUCCESS){
                tstrNetworkId strNetworkId = {NULL, pstrProvInfo->au8SSID, (uint8_t)strlen((char*)(pstrProvInfo->au8SSID)), M2M_WIFI_CH_ALL};
                tstrAuthPsk strAuthPsk = {NULL, pstrProvInfo->au8Password, (uint8_t)strlen((char*)(pstrProvInfo->au8Password))};
                PRINT_DEBUG("PROV SSID : %s\n",pstrProvInfo->au8SSID);
                PRINT_DEBUG("PROV PSK  : %s\n",pstrProvInfo->au8Password);
                m2m_wifi_connect_psk(WIFI_CRED_SAVE_ENCRYPTED, &strNetworkId, &strAuthPsk);
            }
            else{
                PRINT_ERROR("%s", "Provisioning Error\n");
            }
            break;
        
        default:
            PRINT_DEBUG("%s", "Unknown/unhandled wifi event\n");
            break;
    }
}
#endif

#if CLI_EN
void Test1(void)
{
    PRINT_DEBUG("tick;%d\n", ATMEGA4808_RTC_GetTicks());
}
void Test2(void)
{
    printf("This is test 2\n");
}
void Test3(void)
{
    printf("This is test 3\n");
}
#endif

#if TEST_WS2812
void Test_WS2812(void)
{
    if(WS2812_OK != WS2812_Init(20)){
        PRINT_ERROR("%s", "Cannot initialize LED component");
        return;
    }
    WS2812_LedOff();
    WS2812_Update();
    while(1)
    {
        WS2812_SetColorAll(255,0,0);
        WS2812_Update();
        DELAY_milliseconds(500);
        WS2812_SetColorAll(0,255,0);
        WS2812_Update();
        DELAY_milliseconds(500);
        WS2812_SetColorAll(0,0,255);
        WS2812_Update();
        DELAY_milliseconds(500);
    }
}
#endif


void UART2_RXCallback(void)
{
#if CLI_EN
    ch = USART2.RXDATAL;
    USART2.TXDATAL = ch;
    CLI_GetChar(ch);
#endif
}


void SW1_InterruptHandler(void)
{
    //led.LED_SetHigh(BLUE_LED);
}
void SW0_InterruptHandler(void)
{
    //led.LED_SetLow(BLUE_LED);
}


/**
    End of File
*/