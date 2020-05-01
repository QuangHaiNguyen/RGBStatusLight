
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "network/network.h"
#include"cli/cli.h"
#include "scheduler/atmega4808_rtc.h"
#include "led/led.h"
#include "ws2812/WS2812.h"

#define WIFI_EN             0
#define TEST_RTC            0
#define TEST_SCHEDULER      0
#define TEST_RING_BUFF      0


#if TEST_RING_BUFF
#include "utility/ring_buffer.h"
#endif

#if TEST_SCHEDULER
#include "scheduler/scheduler.h"
#endif

#if TEST_RTC
#include "atmega4808_rtc.h"
#endif


#if TEST_WS2812
#include "WS2812.h"
#include "include/winc_legacy.h"
#endif


#if TEST_WS2812
void Test_WS2812(void);
#endif

typedef enum{
    INIT_NETWORK = 0,
    INIT_TCP_SERVER,
    PROVISION,
    CLIENT,
    DISCONNET,
    IDLE,
    ERROR,
}State;

State state = INIT_NETWORK;

NetworkIF_t * interface;
Network_TCPServer * server;
uint8_t *r_ptr;
uint8_t *w_ptr;
uint8_t sw0_debounce = 0;
uint8_t sw1_debounce = 0;
uint32_t ip;
uint32_t last_tick = 0;
static char ch;
CLI_Status cli_stt;

void UART2_RXCallback(void);
void SW1_InterruptHandler(void);
void SW0_InterruptHandler(void);
void callback(void);
void Test1(void);
void Test2(void);
void Test3(void);
void BlinkBlueLED(void);


command_t cmd_table[3] = {
        {"test_1", Test1},
		{"test_2", Test2},
        {"test_3", Test3},
};

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    sei();
    USART2_SetISRCb(UART2_RXCallback, USART2_RX_CB);
    PORTF_SW0_SetInterruptHandler(SW0_InterruptHandler);
    PORTF_SW1_SetInterruptHandler(SW1_InterruptHandler);
    PRINT_INFO("%s", "********************************************\n");
    PRINT_INFO("%s", "System initialized\n");
    
    
#if CLI_EN
    
#endif
    
    
#if TEST_SCHEDULER
    Scheduler_Init();
#endif
    
#if TEST_WS2812
    Test_WS2812();
#endif

#if TEST_RTC
    ATMEGA4808_RTC_Init();
    ATMEGA4808_RTC_Start();
#endif

    /* Replace with your application code */


#if TEST_RING_BUFF
    uint8_t test_read_buff[20] = {0};
    uint8_t avail_mem;
    RingBuffer buff;
    if(BUFF_OK != RingBuffer_Init(&buff, 20))
    {
        while(1);
    }
    if(BUFF_OK != RingBuffer_Push(&buff, "hello\n", 6))
    {
        PRINT_ERROR("%s","buff memory error\n");
        while(1);
    }
    
    RingBuffer_GetAvailableMemory(&buff, &avail_mem);
    PRINT_DEBUG("available memory: %d\n", avail_mem);
    
    RingBuffer_Push(&buff, "world\n", 6);
    
    RingBuffer_GetAvailableMemory(&buff, &avail_mem);
    PRINT_DEBUG("available memory: %d\n", avail_mem);
    
    RingBuffer_Pop(&buff, test_read_buff, 6);
    PRINT_DEBUG("in buffer: %s\n", test_read_buff);
    
    RingBuffer_GetAvailableMemory(&buff, &avail_mem);
    PRINT_DEBUG("available memory: %d\n", avail_mem);
    
    RingBuffer_Pop(&buff, test_read_buff, 6);
    PRINT_DEBUG("in buffer: %s\n", test_read_buff);
    
    RingBuffer_GetAvailableMemory(&buff, &avail_mem);
    PRINT_DEBUG("available memory: %d\n", avail_mem);
    
#endif
    //Turn of the LED
    RED_LED_SetLow();
    GREEN_LED_SetLow();
    BLUE_LED_SetLow();
    YELLOW_LED_SetLow();
    
    //Turn on system tick
    ATMEGA4808_RTC_Init();
    ATMEGA4808_RTC_Start();
    
    //Init the CLI
    CLI_Init(cmd_table, 3);
    CLI_GetVersion(&version, &sub_version, &ssub_version);
    PRINT_INFO("CLI version %02d.%02d.%02d\n", version, sub_version,ssub_version);
    
    //Init RGB led
    if(WS2812_OK != WS2812_Init(20)){
        PRINT_ERROR("%s", "Cannot initialize LED component");
    }
    
    while (1){
        //Handle incomming command
        cli_stt = CLI_ProccessCommand(); 
        if(CLI_CMD_NOTFOUND == cli_stt){
            PRINT_INFO("%s", "command not found\r\n");
        }
        
        //Handle network        
        switch(state){
            case INIT_NETWORK: {              
                interface = (NetworkIF_t*)malloc(sizeof(NetworkIF_t));
                if(interface == NULL){
                    PRINT_ERROR("%s", "cannot allocate memory for wifi interface\n");
                    state = ERROR;
                }
                NetworkIF_Init(interface);
                interface->Network_Init();
                interface->Network_ClientModeStart();
                PRINT_INFO("%s", "Network is initialized\n");
                BLUE_LED_SetLow();
                state = INIT_TCP_SERVER;
                break;
            }
            case INIT_TCP_SERVER:{
                server = (Network_TCPServer*)malloc(sizeof(Network_TCPServerInit));
                if(server == NULL){
                    PRINT_ERROR("%s", "cannot allocate memory for tcp server\n");
                    state = ERROR;
                }
                Network_TCPServerInit(server);
                server->TCPServer_Open(13000, &r_ptr, &w_ptr,  32, &ip);
                server->TCPServer_SetCallback(callback);
                PRINT_INFO("%s", "TCP server is initialized\n");
                GREEN_LED_SetLow();
                state = CLIENT;
                break;
            }
            case PROVISION:{
                GREEN_LED_SetHigh();
                interface->Network_ClientModeStop();
                interface->Network_APMode();
                state = CLIENT;
                PRINT_INFO("%s", "Start Provision\n");
                break;
            }
            case CLIENT:{
                //handle callback
                interface->Network_EventHandle();
                BlinkBlueLED();
                break;
            }
            case DISCONNET:
                //server->TCPServer_Close();
                WINC1500_TCPServerClose();
                server->TCPServer_SetCallback(NULL);
                Network_TCPServerDeInit(server);
                free(server);
                interface->Network_ClientModeStop();
                interface->Network_DeInit();
                NetworkIF_DeInit(interface);
                free(interface);
                PRINT_INFO("%s", "Network is deinitialized\n");
                BLUE_LED_SetHigh();
                state = IDLE;
                break;
            case IDLE:
                //idle do nothing
                break;
            case ERROR:{
                break;
            }
        }
        
    }
}

void Test1(void)
{
    PRINT_DEBUG("%s","test 1\n");
}
void Test2(void)
{
    PRINT_DEBUG("%s","test 1\n");
}
void Test3(void)
{
    PRINT_DEBUG("%s","test 1\n");
}

void UART2_RXCallback(void)
{
    ch = USART2.RXDATAL;
    USART2.TXDATAL = ch;
    CLI_GetChar(ch);
}


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

void BlinkBlueLED(void)
{
    if(ATMEGA4808_RTC_GetTicks() - last_tick < 200){
        
        BLUE_LED_SetLow();
    }
    else if(ATMEGA4808_RTC_GetTicks() - last_tick > 1000){
        last_tick = ATMEGA4808_RTC_GetTicks();
    }
    else{
        BLUE_LED_SetHigh();
    }
}

void callback(void)
{
    YELLOW_LED_Toggle();
    PRINT_DEBUG("%d\n",r_ptr[0] );
    PRINT_DEBUG("%d\n",r_ptr[1] );
    PRINT_DEBUG("%d\n",r_ptr[2] );
    WS2812_SetColorAll(r_ptr[0],r_ptr[1],r_ptr[2]);
    WS2812_Update();
    state = CLIENT;
    memset(w_ptr, 0, 32);
    memcpy(w_ptr, "OK\n", 3);
    WINC1500_TCPServerWrite(32);
}

void SW1_InterruptHandler(void)
{
    if(++sw1_debounce > 5){
        sw1_debounce = 0;
        if(IDLE == state){
            state = INIT_NETWORK;
        }
        else{
            state = DISCONNET;
        }
    }
}
void SW0_InterruptHandler(void)
{
    if(++sw0_debounce > 5){
        sw0_debounce = 0;
        state = PROVISION;
    }
}


/**
    End of File
*/