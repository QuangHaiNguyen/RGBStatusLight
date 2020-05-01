/*******************************************************************************
* Title                 :   network configuration file
* Filename              :   network_conf.h
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
/** @file   network_conf.h
 *  @brief  holding network configuration and common variables
 *  
 */

#ifndef NETWORK_CONF_H
#define	NETWORK_CONF_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "../common.h"

#define USING_WINC  1

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
 * @brief   Server status
**/
typedef enum TCP_SERVER_STATUS{
    TCP_SERVER_OK = 0,
    /**< no error */
    TCP_SERVER_NOT_MEMO,
    /**< cannot allocate memory */
    TCP_SERVER_OPEN_ERR,
    /**< socket open error */
    TCP_SERVER_WRITE_ERR,
    /**< socket send error */
    TCP_SERVER_READ_ERR,
    /**< socket recieve error */
    TCP_SERVER_ACCEPT_ERR,
    /**< socket accept error */
    TCP_SERVER_BIND_ERR,
    /**< socket bind error */
    TCP_SERVER_LISTEN_ERR,
    /**< socket listen error */
}TCP_Server_Status;

/**
 *
 * @brief   Network status
**/
typedef enum NETWORK_STATUS{
    NETWORK_OK = 0,
    /**< no error */
    NETWORK_INIT_ERR,
    /**< network initialzing error */
    NETWORK_AP_ERR,
    /**< starting AP mode error */
    NETWORK_CLIENT_CONN_ERR,
    /**< connect to an AP error  */
    NETWORK_PROVISION_ERR,
    /**< provisioning error  */
    NETWORK_PROVISION_MODE,
    /**< network in provisioning mode */
    NETWORK_CLIENT_MODE,
    /**< network in client mode */
    NETWORK_AP_MODE,
    /**< network in AP mode */
    NETWORK_CONNECTED,
    /**< connected to a network */
    NETWORK_DISCONNECTED,
    /**< disconnected from a network */
}Network_Status;

#if USING_WINC
#include "network_winc1500.h"
#include "winc1500_tcp_server.h"
#endif



#endif	/* NETWORK_CONF_H */

