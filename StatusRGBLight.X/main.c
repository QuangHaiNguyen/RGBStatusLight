
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
#define TEST_NETWORK        0
#define TEST_RING_BUFF      0

#if TEST_RING_BUFF
#include "utility/ring_buffer.h"
#endif

#if TEST_NETWORK
#include "network/network.h"
static Network *TaskPointer = NULL;
#endif

#if TEST_SCHEDULER
#include "scheduler/scheduler.h"
#endif

#if TEST_RTC
#include "atmega4808_rtc.h"
#endif

#if WIFI_EN
#include "mcc_generated_files/winc/m2m/m2m_wifi.h"
#include "mcc_generated_files/winc/m2m/m2m_types.h"
#include "common/winc_defines.h"
#include "driver/winc_adapter.h"

#define MAIN_WIFI_M2M_BUFFER_SIZE 1460
#define MAIN_WIFI_M2M_PRODUCT_NAME "NMCTemp"

#define MAIN_WIFI_M2M_SERVER_PORT       13000 
#define MAIN_WLAN_SSID                  "MommyShark"
#define MAIN_WLAN_AUTH                  M2M_WIFI_SEC_WPA_PSK
#define MAIN_WLAN_PSK                   "?HnTb75212!"
/** Receive buffer definition. */
static uint8_t gau8SocketTestBuffer[MAIN_WIFI_M2M_BUFFER_SIZE];

/** Socket for TCP communication */
static SOCKET tcp_server_socket = -1;
static SOCKET tcp_client_socket = -1;

/** Wi-Fi connection state */
static uint8_t wifi_connected;

/** Message format definitions. */
typedef struct s_msg_wifi_product {
	uint8_t name[9];
} t_msg_wifi_product;

/** Message format declarations. */
static t_msg_wifi_product msg_wifi_product = {
    .name = MAIN_WIFI_M2M_PRODUCT_NAME,
};

tstrWifiInitParam wifi_param;
    
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg);
void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg);
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
    
#if WIFI_EN
    struct sockaddr_in addr;
    
    winc_adapter_init();
    
    /* Initialize socket address structure. */
	addr.sin_family      = AF_INET;
	addr.sin_port        = _htons(MAIN_WIFI_M2M_SERVER_PORT);
	addr.sin_addr.s_addr = 0;
    
    wifi_param.pfAppWifiCb = Wifi_EventCallback;
    
    /* Initialize socket module */
	socketInit();
	registerSocketCallback(socket_cb, NULL);
    
    
    
    if(!M2M_SUCCESS == m2m_wifi_init(&wifi_param)){
        PRINT_ERROR("%s", "Initialize wifi error\n");
        while(1);
    }
    
#if 0        
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
    PRINT_DEBUG("%s", "AP Started\n");
#endif
    /* Connect to router. */
 
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, 
            sizeof(MAIN_WLAN_SSID), 
            MAIN_WLAN_AUTH, 
            (char *)MAIN_WLAN_PSK, 
            M2M_WIFI_CH_ALL);
    
#endif
    /* Replace with your application code */
#if TEST_NETWORK
    NetworkInit();
    TaskPointer = GetNetworkIFList();
    PRINT_DEBUG("Using: %s\n", TaskPointer[0].name);
    TaskPointer[0].interface->Network_Init();
    TaskPointer[0].interface->Network_ClientMode();
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
        TaskPointer[0].interface->Network_EventHandle();
#endif
        
#if TEST_SCHEDULER
        Scheduler_Run();
#endif
#if WIFI_EN
        m2m_wifi_handle_events(NULL);
        if (wifi_connected == M2M_WIFI_CONNECTED) {
			if (tcp_server_socket < 0) {
				/* Open TCP server socket */
				if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
					PRINT_DEBUG("%s", "failed to create TCP server socket error!\r\n");
					continue;
				}

				/* Bind service*/
				bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
			}
		}
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
        
        case M2M_WIFI_REQ_DHCP_CONF: {
            uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
            wifi_connected        = 1;
            PRINT_DEBUG("wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\r\n",
                    pu8IPAddress[0],
                    pu8IPAddress[1],
                    pu8IPAddress[2],
                    pu8IPAddress[3]);
            } 
        break;
        default:
            PRINT_DEBUG("%s", "Unknown/unhandled wifi event\n");
            break;
    }
}

static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
    switch (u8Msg) {
	/* Socket bind */
	case SOCKET_MSG_BIND: {
		tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
		if (pstrBind && pstrBind->status == 0) {
			PRINT_DEBUG("%s", "socket_cb: bind success!\r\n");
			listen(tcp_server_socket, 0);
		} else {
			PRINT_DEBUG("%s", "socket_cb: bind error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	} break;

	/* Socket listen */
	case SOCKET_MSG_LISTEN: {
		tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
		if (pstrListen && pstrListen->status == 0) {
			PRINT_DEBUG("%s", "socket_cb: listen success!\r\n");
			accept(tcp_server_socket, NULL, NULL);
		} else {
			PRINT_DEBUG("%s", "socket_cb: listen error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	} break;

	/* Connect accept */
	case SOCKET_MSG_ACCEPT: {
		tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
		if (pstrAccept) {
			PRINT_DEBUG("%s", "socket_cb: accept success!\r\n");
			accept(tcp_server_socket, NULL, NULL);
			tcp_client_socket = pstrAccept->sock;
			recv(tcp_client_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
		} else {
			PRINT_DEBUG("%s", "socket_cb: accept error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	} break;

	/* Message send */
	case SOCKET_MSG_SEND: {
		PRINT_DEBUG("%s", "socket_cb: send success!\r\n");
		PRINT_DEBUG("%s", "TCP Server Test Complete!\r\n");
		PRINT_DEBUG("%s", "close socket\n");
		close(tcp_client_socket);
		close(tcp_server_socket);
	} break;

	/* Message receive */
	case SOCKET_MSG_RECV: {
		tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
		if (pstrRecv && pstrRecv->s16BufferSize > 0) {
			PRINT_DEBUG("%s", "socket_cb: recv success!\r\n");
			send(tcp_client_socket, &msg_wifi_product, sizeof(t_msg_wifi_product), 0);
		} else {
			PRINT_DEBUG("%s", "socket_cb: recv error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	}

	break;

	default:
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