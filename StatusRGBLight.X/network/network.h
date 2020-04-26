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
    uint8_t (*TCPServer_Open)( uint16_t port,
                                uint8_t **socket_read_data,
                                uint8_t **socket_write_data,
                                uint16_t socket_data_size,
                                uint32_t *ip);
    uint8_t (*TCPServer_Close)(void);
    uint8_t (*TCPServer_Read)(uint16_t num_of_byte);
    uint8_t (*TCPServer_Write)(uint16_t num_of_byte);
    uint8_t (*TCPServer_SetCallback)(TCPServer_cb_t  cb);
}Network_TCPServer;


void NetworkIF_Init(NetworkIF_t *interface);
void NetworkIF_DeInit(NetworkIF_t *interface);
void Network_TCPServerInit(Network_TCPServer * server);
void Network_TCPServerDeInit(Network_TCPServer * server);

#endif	/* NETWOR_H */

