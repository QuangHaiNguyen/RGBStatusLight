
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "cli.h"
#include "led.h"
#include "debug.h"

#include "mcc_generated_files/winc/m2m/m2m_wifi.h"
#include "mcc_generated_files/winc/m2m/m2m_types.h"
#include "common/winc_defines.h"
#include "driver/winc_adapter.h"

#define CLI_EN      0
#define WIFI_EN     0
#define BIT_1       3750
#define BIT_0       1875

void Test1(void);
void Test2(void);
void Test3(void);
void UART2_RXCallback(void);
void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg);
void CaptureCompareCallback(void);
void OverflowCallback(void);
static char ch;
CLI_Status cli_stt;
bool toogle_flag = true;


command_t cmd_table[3] = {
        {"test_1", Test1},
		{"test_2", Test2},
        {"test_3", Test3},
};
uint8_t version;
uint8_t sub_version;
uint8_t ssub_version;
Led_Comp led; 
tstrWifiInitParam wifi_param;
    

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    winc_adapter_init();
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
    
    TCA0_EnableInterrupt();
    TCA0.SINGLE.CMP0 = BIT_1;
    TCA0_SetCMP0IsrCallback((TCA0_cb_t)CaptureCompareCallback);
    TCA0_SetOVFIsrCallback((TCA0_cb_t)OverflowCallback);
    PRINT_DEBUG("%s", "PWM Start\n");

#if WIFI_EN
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

void Test1(void)
{
    printf("This is test 1\n");
}
void Test2(void)
{
    printf("This is test 2\n");
}
void Test3(void)
{
    printf("This is test 3\n");
}

void UART2_RXCallback(void)
{
    ch = USART2.RXDATAL;
    USART2.TXDATAL = ch;
    CLI_GetChar(ch);
}

void CaptureCompareCallback(void)
{
    
}

void OverflowCallback(void)
{
    if(toogle_flag){
        TCA0.SINGLE.CMP0 = BIT_0;
        toogle_flag = false;
    }
    else{
        TCA0.SINGLE.CMP0 = BIT_1;
        toogle_flag = true;
    }
}
/**
    End of File
*/