
#include "network.h"

void NetworkIF_Init(NetworkIF_t *interface)
{
#if USING_WINC
    interface->Network_Init = WINC1500_Init;
    interface->Network_DeInit = WINC1500_DeInit;
    interface->Network_APMode = WINC1500_StartAP;
    interface->Network_ClientMode = WINC1500_StartClient;
    interface->Network_EventHandle = WINC1500_EventHandle;
#endif
}
void NetworkIF_DeInit(NetworkIF_t *interface)
{
    interface = NULL;
}

void Network_TCPServerInit(Network_TCPServer * server)
{
#if USING_WINC
    server->TCPServer_Open = WINC1500_TCPServerOpen;
    server->TCPServer_Close = WINC1500_TCPServerClose;
    server->TCPServer_Read = WINC1500_TCPServerRead;
    server->TCPServer_Write = WINC1500_TCPServerWrite;
    server->TCPServer_SetCallback = WINC1500_TCPServerSetCallback;
#endif
}
void Network_TCPServerDeInit(Network_TCPServer * server)
{
    server = NULL;
}