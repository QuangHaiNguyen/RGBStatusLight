/*******************************************************************************
* Title                 :   winc1500 tcp server component
* Filename              :   winc1500_tcp_server.h
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
/** @file   winc1500_tcp_server.h
 *  @brief  hardware implementation of a tcp server based on winc1500
 *  
 */

#ifndef TCP_CLIENT_H
#define	TCP_CLIENT_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "network_conf.h"

#include "../mcc_generated_files/winc/m2m/m2m_wifi.h"
#include "../mcc_generated_files/winc/m2m/m2m_types.h"
#include "../mcc_generated_files/winc/common/winc_defines.h"
#include "../mcc_generated_files/winc/driver/winc_adapter.h"

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
//None

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None
typedef void (*TCPServer_cb_t)(void);

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
//None

/******************************************************************************
* Function Prototypes
*******************************************************************************/
TCP_Server_Status WINC1500_TCPServerOpen( uint16_t port,
                                uint8_t **socket_read_data,
                                uint8_t **socket_write_data,
                                uint16_t socket_data_size,
                                uint32_t *ip);

TCP_Server_Status WINC1500_TCPServerClose();
TCP_Server_Status WINC1500_TCPServerWrite(uint16_t num_of_byte);
TCP_Server_Status WINC1500_TCPServerRead(uint16_t num_of_byte);
TCP_Server_Status WINC1500_TCPServerSetCallback(TCPServer_cb_t  cb);
TCP_Server_Status WINC1500_TCPServerGetStatus(void);

#endif	/* TCP_CLIENT_H */
/*** End of File **************************************************************/


