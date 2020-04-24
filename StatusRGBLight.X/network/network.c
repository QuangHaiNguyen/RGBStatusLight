
#include "network.h"

NetworkIF_t winc1500;

static Network network_list[]= {
#if USING_WINC
    {
        "winc1500",
        false,
        NULL,
    },
#endif
};

Network * const GetNetworkIFList(void)
{
    return network_list;
}

uint8_t GetNumberOfNetwork(void)
{
    static uint8_t const num_of_IF = sizeof(network_list) / sizeof(*network_list);
    return num_of_IF;
}

void NetworkInit(void)
{
    network_list[0].isActive = true;
    network_list[0].interface = &winc1500;
    network_list[0].interface ->Network_Init = WINC1500_Init;
    network_list[0].interface->Network_DeInit = WINC1500_DeInit;
    network_list[0].interface->Network_APMode = WINC1500_StartAP;
    network_list[0].interface->Network_ClientMode = WINC1500_StartClient;
    network_list[0].interface->Network_EventHandle = WINC1500_EventHandle;
}