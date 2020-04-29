
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "network/network.h"

#define WIFI_EN             0
#define TEST_WS2812         0
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
    INIT = 0,
    PROVISION,
    CLIENT,
    IDLE,
    ERROR,
}State;

State state = INIT;

NetworkIF_t * interface;
Network_TCPServer * server;
uint8_t *r_ptr;
uint8_t *w_ptr;
uint32_t ip;

void UART2_RXCallback(void);
void SW1_InterruptHandler(void);
void SW0_InterruptHandler(void);
void callback(void);

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
    interface = (NetworkIF_t*)malloc(sizeof(NetworkIF_t));
    if(interface == NULL){
        PRINT_ERROR("%s", "cannot allocate memory for wifi interface\n");
        state = ERROR;
    }
    NetworkIF_Init(interface);
    interface->Network_Init();
    interface->Network_ClientModeStart();

    server = (Network_TCPServer*)malloc(sizeof(Network_TCPServerInit));
    if(server == NULL){
        PRINT_ERROR("%s", "cannot allocate memory for tcp server\n");
        state = ERROR;
    }
    Network_TCPServerInit(server);
    server->TCPServer_Open(13000, &r_ptr, &w_ptr,  32, &ip);

    server->TCPServer_SetCallback(callback);
    while (1){
        interface->Network_EventHandle();
    }
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


void callback(void)
{
    PRINT_DEBUG("message %s\n", r_ptr);
    memset(w_ptr, 0, 32);
    memcpy(w_ptr, "OK\n", 3);
    server->TCPServer_Write(32);
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