
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "led.h"

#define CLI_EN              0
#define WIFI_EN             0
#define TEST_WS2812         0
#define TEST_RTC            0
#define TEST_SCHEDULER      0
#define TEST_NETWORK        1
#define TEST_RING_BUFF      0
#define TEST_TCP            1

#if TEST_RING_BUFF
#include "utility/ring_buffer.h"
#endif

#if TEST_TCP
#include "network/network.h"
void callback(void);
uint8_t *r_ptr;
uint8_t *w_ptr;
Network_TCPServer * server;
#endif

#if TEST_NETWORK
#include "network/network.h"
#endif

#if TEST_SCHEDULER
#include "scheduler/scheduler.h"
#endif

#if TEST_RTC
#include "atmega4808_rtc.h"
#endif


#if CLI_EN
#include "cli.h"
#endif 

#if TEST_WS2812
#include "WS2812.h"
#include "include/winc_legacy.h"
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
#if TEST_NETWORK
    
    NetworkIF_t * interface;
    interface = (NetworkIF_t*)malloc(sizeof(NetworkIF_t));
    if(interface == NULL){
        PRINT_ERROR("%s", "cannot allocate memory for wifi interface\n");
        while(1);
    }
    NetworkIF_Init(interface);
    interface->Network_Init();
    interface->Network_ClientModeStart();
    
#endif
    
#if TEST_TCP
    uint32_t ip;
    server = (Network_TCPServer*)malloc(sizeof(Network_TCPServerInit));
    if(server == NULL){
        PRINT_ERROR("%s", "cannot allocate memory for tcp server\n");
        while(1);
    }
    Network_TCPServerInit(server);
    server->TCPServer_Open(13000, &r_ptr, &w_ptr,  20, &ip);
    
    server->TCPServer_SetCallback(callback);
#endif

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
    while (1){
#if TEST_NETWORK
        interface->Network_EventHandle();
#endif
        
#if TEST_SCHEDULER
        Scheduler_Run();
#endif
        
#if CLI_EN
        cli_stt = CLI_ProccessCommand();
        if(CLI_CMD_NOTFOUND == cli_stt){
            printf("command not found\r\n");
        }
#endif
    }
}


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

#if TEST_TCP
void callback(void)
{
    PRINT_DEBUG("message %s\n", r_ptr);
    memset(w_ptr, 0, 32);
    memcpy(w_ptr, "OK\n", 3);
    WINC1500_TCPServerWrite(32);
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