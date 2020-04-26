/*******************************************************************************
* Title                 :   winc1500 network component
* Filename              :   network_winc1500.h
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
/** @file   network_winc1500.h
 *  @brief  hardware implementation of the wireless connection. The 
 *  implementation can be used as an AP mode for ssid and password provisioning,
 *  or client mode 
 *  
 */
#ifndef WINC1500_H
#define	WINC1500_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "../common.h"
#include "network_conf.h"

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
//None

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
//None

/******************************************************************************
* Function Prototypes
*******************************************************************************/
Network_Status WINC1500_Init(void);
Network_Status WINC1500_DeInit(void);
Network_Status WINC1500_StartAP(void);
Network_Status WINC1500_StartClient(void);
Network_Status WINC1500_EventHandle(void);
Network_Status WINC1500_GetStatus(void);
Network_Status WINC1500_GetIP(uint32_t * ip);
Network_Status WINC1500_StopClient(void);

#endif	/* WINC1500_H */
/*** End of File **************************************************************/
