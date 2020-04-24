/* 
 * File:   networ.h
 * Author: haing
 *
 * Created on April 24, 2020, 2:02 PM
 */

#ifndef NETWOR_H
#define	NETWOR_H



#include "network_conf.h"

typedef struct{
    uint8_t (*Network_Init)(void);
    uint8_t (*Network_DeInit)(void);
    uint8_t (*Network_APMode)(void);
    uint8_t (*Network_ClientMode)(void);
    uint8_t (*Network_EventHandle)(void);
}NetworkIF_t;


typedef struct{
    uint8_t (*TCPServer_Init)(void);
    uint8_t (*TCPServer_DeInit)(void);
    uint8_t (*TCPServer_Bind)(void);
    uint8_t (*TCPServer_Close)(void);
    uint8_t (*TCPServer_Send)(void);
    uint8_t (*TCPServer_Recieve)(void);
    uint8_t (*TCPServer_GetIP)(uint32_t * ip);
}TCPServer;

typedef struct{
    char const *name;
    bool isActive;
    NetworkIF_t *interface;
}Network;


uint8_t GetNumberOfNetwork(void);
Network * const GetNetworkIFList(void);

void NetworkInit(void);
void NetworkDeInit(void);

#endif	/* NETWOR_H */

