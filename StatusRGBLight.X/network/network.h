/*******************************************************************************
* Title                 :   network component
* Filename              :   network.h
* Author                :   Quang Hai Nguyen
* Origin Date           :   26.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** INTERFACE CHANGE LIST *****************************************
*
*  Date         Version     Author              Description 
*  26.04.2020   1.0.0       Quang Hai Nguyen    Interface Created.
*
*******************************************************************************/
/** @file   network.h
 *  @brief  the adapter for the network functions. It contains the common API to 
 *          interact with the underlying hardware module. 
 *  
 */
#ifndef NETWOR_H
#define	NETWOR_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "network_conf.h"

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
//None

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/**
 *
 * @brief   Contain the HAL API to interact with the underlying wireless module. 
 *          User must point these function pointers to the actual implementation
**/
typedef struct{
    Network_Status (*Network_Init)(void);
    /**< pointer to network init function */
    Network_Status (*Network_DeInit)(void);
    /**< pointer to network de init function */
    Network_Status (*Network_APMode)(void);
    /**< pointer to start AP mode function */
    Network_Status (*Network_ClientModeStart)(void);
    /**< pointer to start client mode function */
    Network_Status (*Network_ClientModeStop)(void);
    /**< pointer to stop client mode function */
    Network_Status (*Network_EventHandle)(void);
    /**< pointer to event handler function */
    Network_Status (*Network_GetStatus)(void);
    /**< pointer to get status function */
    Network_Status (*Network_GetIP)(uint32_t * ip);
    /**< pointer to get ip function */
}NetworkIF_t;


/**
 *
 * @brief   Contain the HAL API to start a TCP server
**/
typedef struct{
    TCP_Server_Status (*TCPServer_Open)( uint16_t port,
                                uint8_t **socket_read_data,
                                uint8_t **socket_write_data,
                                uint16_t socket_data_size,
                                uint32_t *ip);
    /**< pointer to open server function */
    TCP_Server_Status (*TCPServer_Close)(void);
    /**< pointer to close server function */
    TCP_Server_Status (*TCPServer_Read)(uint16_t num_of_byte);
    /**< pointer to read data from socket function */
    TCP_Server_Status (*TCPServer_Write)(uint16_t num_of_byte);
    /**< pointer to write data to socket function */
    TCP_Server_Status (*TCPServer_SetCallback)(TCPServer_cb_t  cb);
    /**< pointer to set callback function */
    TCP_Server_Status (*TCPServer_GetStatus)(void);
    /**< pointer to get server status function */
}Network_TCPServer;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
//None

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void NetworkIF_Init(NetworkIF_t *interface);
void NetworkIF_DeInit(NetworkIF_t *interface);
void Network_TCPServerInit(Network_TCPServer * server);
void Network_TCPServerDeInit(Network_TCPServer * server);

#endif	/* NETWOR_H */

