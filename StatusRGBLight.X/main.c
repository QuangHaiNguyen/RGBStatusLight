
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "network/network.h"
#include"cli/cli.h"
#include "scheduler/atmega4808_rtc.h"
#include "led/led.h"
#include "ws2812/WS2812.h"
#include "include/winc_legacy.h"

#define SEND_OK()       w_ptr[0] = 0xA7; w_ptr[1] = 0x02; w_ptr[2] = 0x4F; w_ptr[3] = 0x4B;     \
                        w_ptr[4] = w_ptr[0] + w_ptr[1] + w_ptr[2] + w_ptr[3];                   \
                        WINC1500_TCPServerWrite(5);

#define SEND_ERR(x)     w_ptr[0] = 0xA8; w_ptr[1] = 0x01; w_ptr[2] = x; \
                        w_ptr[3] = w_ptr[0] + w_ptr[1] + w_ptr[2];      \
                        WINC1500_TCPServerWrite(4);

typedef enum{
    CRC_ERR = 0xB0,
    WS2812_ERR,
}Reply;

typedef enum{
    INIT_NETWORK = 0,
    INIT_TCP_SERVER,
    PROVISION,
    CLIENT,
    DISCONNET,
    IDLE,
    PROCESSING,        
    ERROR,
}State;

typedef enum{
    MSG_COLOR_ALL = 0xA0,
    MSG_COLOR_INDIVI,
    MSG_COLOR_PATCH,
    MSG_COLOR_CUSTOM,
    MSG_HELLO,
    MSG_INIT,
    MSG_DEINIT,
    END_OF_MSG,
}Opt_Code;

typedef struct{
    Opt_Code opt_code;
    void (*function)(uint8_t *msg);
}MSG_FROM_CLIENT;

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
WS2812_Status ws2812_status = WS2812_NOT_INIT;

void UART2_RXCallback(void);
void SW1_InterruptHandler(void);
void SW0_InterruptHandler(void);
void callback(void);
void Test1(void);
void Test2(void);
void Test3(void);
void BlinkBlueLED(void);

void MSG_COLOR_ALL_Handle(uint8_t *msg);
void MSG_COLOR_INDIVI_Handle(uint8_t *msg);
void MSG_COLOR_PATCH_Handle(uint8_t *msg);
void MSG_COLOR_CUSTOM_handle(uint8_t *msg);
void MSG_HELLO_Handle(uint8_t *msg);
void MSG_INIT_Handle(uint8_t *msg);
void MSG_DEINIT_Handle(uint8_t *msg);
bool VerifyCRC(uint8_t *msg);
void ProcessCommand(void);

command_t cmd_table[3] = {
        {"test_1", Test1},
		{"test_2", Test2},
        {"test_3", Test3},
};

const MSG_FROM_CLIENT msg_list[] = {
    {   MSG_COLOR_ALL,      MSG_COLOR_ALL_Handle},
    {   MSG_COLOR_INDIVI,   MSG_COLOR_INDIVI_Handle},
    {   MSG_COLOR_PATCH,    MSG_COLOR_PATCH_Handle},
    {   MSG_COLOR_CUSTOM,   MSG_COLOR_CUSTOM_handle},
    {   MSG_HELLO,          MSG_HELLO_Handle},
    {   MSG_INIT,           MSG_INIT_Handle},
    {   MSG_DEINIT,         MSG_DEINIT_Handle},
    {   END_OF_MSG,         NULL},
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
    
    

    /* Replace with your application code */

    //Turn off the LED
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
            case PROCESSING:
                
                state = CLIENT;
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
bool VerifyCRC(uint8_t *msg)
{
    uint32_t sum = 0;
    PRINT_DEBUG("data length: %02x\n", msg[1]);
    PRINT_DEBUG("CRC: %02x\n", msg[msg[1] + 2]);
    for (uint16_t i = 0; i < msg[1] + 2; i++)
    {
        sum = sum + msg[i];
    }
    if((sum & 0xFF) == msg[msg[1] + 2])
    {
        PRINT_DEBUG("%s", "CRC correct!\n");
        return true;
    }
    else{
        PRINT_DEBUG("%s", "CRC wrong!\n");
        return false;
    }
}

void ProcessCommand(void)
{
    
    if(VerifyCRC(r_ptr) == false){
        SEND_ERR(CRC_ERR);
        return;
    }
        
    for (uint8_t i = 0; i != END_OF_MSG; i++){
        if(msg_list[i].opt_code == r_ptr[0]){
            msg_list[i].function(r_ptr);
            return;
        }
    }
}

void MSG_COLOR_ALL_Handle(uint8_t *msg)
{
    if(ws2812_status != WS2812_OK){
        SEND_ERR(WS2812_ERR);
        return;
    }
    WS2812_SetColorAll(msg[2], msg[3], msg[4]);
    WS2812_Update();
    SEND_OK();
    
}

void MSG_COLOR_INDIVI_Handle(uint8_t *msg)
{
}

void MSG_COLOR_PATCH_Handle(uint8_t *msg)
{
}

void MSG_COLOR_CUSTOM_handle(uint8_t *msg)
{
  
}

void MSG_HELLO_Handle(uint8_t *msg)
{
    PRINT_DEBUG("%s", "Got hello msg\n");
    if(msg[2] != 0x41)
        return;
    if(msg[3] != 0x54)
        return;
    memset(w_ptr, 0, 32);
    SEND_OK();
}

void MSG_INIT_Handle(uint8_t *msg)
{
    //Init RGB led
    if(ws2812_status != WS2812_NOT_INIT){
        //WS2812 is existing
        WS2812_DeInit();
    }
    
    ws2812_status = WS2812_Init(msg[2]);
    if(WS2812_OK != ws2812_status){
        PRINT_ERROR("%s", "Cannot initialize LED component");
        SEND_ERR(WS2812_ERR);
        return;
    }
    SEND_OK();
    return;
}

void MSG_DEINIT_Handle(uint8_t *msg)
{
    WS2812_DeInit();
    SEND_OK();
}

void callback(void)
{
    YELLOW_LED_Toggle();
    ProcessCommand();
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