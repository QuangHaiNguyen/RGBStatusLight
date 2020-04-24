#include "winc1500_tcp_server.h"

#define UFFER_SIZE 20
static uint8_t gau8SocketTestBuffer[UFFER_SIZE];
static SOCKET tcp_server_socket = -1;
static SOCKET tcp_client_socket = -1;
static struct sockaddr_in addr;
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg);

uint8_t WINC1500_TCPServerInit(tpfAppSocketCb socket_cb, uint16_t port_number)
{
    /* Initialize socket address structure. */
	addr.sin_family      = AF_INET;
	addr.sin_port        = _htons(port_number);
	addr.sin_addr.s_addr = 0;
    
    /* Initialize socket module */
	socketInit();
	registerSocketCallback(socket_cb, NULL);
    return 0;
}

uint8_t WINC1500_TCPServerDeInit(void)
{
    close(tcp_server_socket);
    tcp_server_socket = -1;
    tcp_client_socket = -1;
    return 0;
}

uint8_t WINC1500_TCPServerBind(void)
{
    if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        PRINT_ERROR("%s", "failed to create TCP server socket error!\r\n");
        return -1;
    }

    /* Bind service*/
    if (bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != SOCK_ERR_NO_ERROR){
        PRINT_ERROR("%s", "socket binding error!\r\n");
        return -1;
    }
    return 0;
}

uint8_t WINC1500_TCPServerClose(void)
{
    close(tcp_server_socket);
    return 0;
}

uint8_t WINC1500_TCPServerSend(uint8_t *data, uint8_t data_size)
{
    send(tcp_client_socket, data, data_size, 0);
    return 0;
}

uint8_t WINC1500_TCPServerRecieve(uint8_t * data, uint8_t * size)
{
    recv(tcp_client_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
    return 0;
}

uint8_t WINC1500_TCPServerGetIP(uint32_t *ip)
{
    *ip = (uint32_t)addr.sin_addr.s_addr;
    return 0;
}
