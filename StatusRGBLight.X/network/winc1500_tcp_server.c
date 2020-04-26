#include "winc1500_tcp_server.h"

#define MAIN_WIFI_M2M_PRODUCT_NAME "NMCTemp"

SOCKET tcp_server_socket;
SOCKET tcp_client_socket;
uint8_t * read_data;
uint8_t * write_data;
uint16_t size;

void (*read_cb)(void);
static struct  sockaddr_in addr;

static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg);
static void WINC1500_TCPServerReOpen(void);

uint8_t WINC1500_TCPServerOpen( uint16_t port,
                                uint8_t **socket_read_data,
                                uint8_t **socket_write_data,
                                uint16_t socket_data_size,
                                uint32_t *ip)
{
    size = socket_data_size;
    read_data = (uint8_t*)malloc(size *sizeof(uint8_t));
    write_data = (uint8_t*)malloc(size *sizeof(uint8_t));
    
    /* Initialize socket address structure. */
	addr.sin_family      = AF_INET;
	addr.sin_port        = _htons(port);
	addr.sin_addr.s_addr = 0;
    
    //must add data validation
    
    socketInit();
    registerSocketCallback(socket_cb, NULL);
    
    if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        PRINT_ERROR("%s", "failed to create TCP server socket error!\r\n");
        return -1;
    }

    /* Bind service*/
    if (bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != SOCK_ERR_NO_ERROR){
        PRINT_ERROR("%s", "socket binding error!\r\n");
        return -1;
    }
    *ip = (uint32_t)addr.sin_addr.s_addr;
    *socket_read_data = read_data;
    *socket_write_data = write_data;
    
    listen(tcp_server_socket, 0);

    return 0;
}
uint8_t WINC1500_TCPServerClose()
{
    free(read_data);
    free(write_data);
    close(tcp_server_socket);
    tcp_client_socket = -1;
    tcp_server_socket = -1;
    return 0;
}
uint8_t WINC1500_TCPServerWrite(uint16_t num_of_byte)
{
    send(tcp_client_socket, write_data, num_of_byte, 0);
    return 0;
}
uint8_t WINC1500_TCPServerRead(uint16_t num_of_byte)
{
    memset(read_data, 0, 32);
    recv(tcp_client_socket, read_data, num_of_byte, 0);
    return 0;
}

uint8_t WINC1500_TCPServerSetCallback(TCPServer_cb_t  cb)
{
    read_cb = cb;
    return 0;
}

static void WINC1500_TCPServerReOpen(void)
{
    //must add data validation
    close(tcp_server_socket);
    tcp_server_socket = -1;
    tcp_client_socket = -1;
    
    //socketInit();
    //registerSocketCallback(socket_cb, NULL);
    
    if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        PRINT_ERROR("%s", "failed to create TCP server socket error!\r\n");
    }

    /* Bind service*/
    if (bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != SOCK_ERR_NO_ERROR){
        PRINT_ERROR("%s", "socket binding error!\r\n");
    }    
    listen(tcp_server_socket, 0);
    return;
}

#if 1
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
    switch (u8Msg) {
	/* Socket bind */
	case SOCKET_MSG_BIND: {
		tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
		if (pstrBind && pstrBind->status == 0) {
			PRINT_DEBUG("%s", "socket bind success!\r\n");
            listen(tcp_server_socket, 0);
		} else {
			PRINT_DEBUG("%s", "socket bind error!\r\n");
            WINC1500_TCPServerReOpen();
		}
	} break;

	/* Socket listen */
	case SOCKET_MSG_LISTEN: {
		tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
		if (pstrListen && pstrListen->status == 0) {
			PRINT_DEBUG("%s", "socket listen success!\r\n");
			accept(tcp_server_socket, NULL, NULL);
		} else {
			PRINT_DEBUG("%s", "socket listen error!\r\n");
            WINC1500_TCPServerReOpen();
		}
	} break;

	/* Connect accept */
	case SOCKET_MSG_ACCEPT: {
		tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
		if (pstrAccept) {
			PRINT_DEBUG("%s", "socket accept success!\r\n");
			accept(tcp_server_socket, NULL, NULL);
			tcp_client_socket = pstrAccept->sock;
            if(tcp_client_socket > 0){
                WINC1500_TCPServerRead(size);
            }
            else{
                PRINT_DEBUG("%s", "socket accept success!\r\n");
            }
		} else {
			PRINT_DEBUG("%s", "socket_cb: accept error!\r\n");
            WINC1500_TCPServerReOpen();
		}
	} break;

	/* Message send */
	case SOCKET_MSG_SEND: {
		PRINT_DEBUG("%s", "socket send success!\r\n");
	} break;

	/* Message receive */
	case SOCKET_MSG_RECV: {
		tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
		if (pstrRecv && pstrRecv->s16BufferSize > 0) {
			PRINT_DEBUG("%s", "socket recv success!\r\n");
            if (read_cb != NULL)
                (*read_cb)();
            WINC1500_TCPServerRead(size);
		} else {
			PRINT_DEBUG("%s", "socket_cb: recv error!\r\n");
			close(tcp_server_socket);
            WINC1500_TCPServerReOpen();
		}
	}

	break;

	default:
		break;
	}
}
#endif