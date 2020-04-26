/*******************************************************************************
* Title                 :   network component   
* Filename              :   network.c
* Author                :   Quang Hai Nguyen
* Origin Date           :   26.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** SOURCE REVISION LOG *****************************************
*
*  Date         Version     Author              Description 
*  26.04.2020   0.0.99       Quang Hai Nguyen    Initial Release.
*
*******************************************************************************/
/** @file  network.c
 *  @brief This is the source file for network component. Containing the init 
 *  function which point to the hardware implementation and the de-init function, 
 *  which frees the resource
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "network.h"

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : NetworkIF_Init
*//** 
* \b Description:
*
* This function points the common network API to the actual hardware implementation 
*
* PRE-CONDITION: Underlying hardware implementation must be existing
*
* POST-CONDITION: None
* 
* @param    *interface: (IN)structure holding the network interface
* @return   None
*
* \b Example Example:
* @code
* NetworkIF_t *interface = NULL;
* interface = (NetworkIF_t*)malloc(sizeof(NetworkIF_t));
* if(NULL == interface){
*       printf("not enough memory\n");
*       //error handler 
* }
* NetworkIF_Init(interface); 
* @endcode
*
* @see NetworkIF_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void NetworkIF_Init(NetworkIF_t *interface)
{
#if USING_WINC
    interface->Network_Init = WINC1500_Init;
    interface->Network_DeInit = WINC1500_DeInit;
    interface->Network_APMode = WINC1500_StartAP;
    interface->Network_ClientModeStart = WINC1500_StartClient;
    interface->Network_ClientModeStop = WINC1500_StopClient;
    interface->Network_EventHandle = WINC1500_EventHandle;
    interface->Network_GetStatus = WINC1500_GetStatus;
    interface->Network_GetIP = WINC1500_GetIP;
#endif
}

/******************************************************************************
* Function : NetworkIF_DeInit
*//** 
* \b Description:
*
* This function de-reference the interface pointer and free the resource.
*
* PRE-CONDITION: None
*
* POST-CONDITION: None
* 
* @param    *interface: (IN)structure holding the network interface
* @return   None
*
* \b Example Example:
* @code
* NetworkIF_t *interface = NULL;
* interface = (NetworkIF_t*)malloc(sizeof(NetworkIF_t));
* if(NULL == interface){
*       printf("not enough memory\n");
*       //error handler 
* }
* NetworkIF_Init(interface);
* //do something
* NetworkIF_DeInit(interface);   
* @endcode
*
* @see NetworkIF_DeInit
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void NetworkIF_DeInit(NetworkIF_t *interface)
{
    interface = NULL;
}

/******************************************************************************
* Function : Network_TCPServerInit
*//** 
* \b Description:
*
* This function points the common TCP API to the actual hardware implementation 
*
* PRE-CONDITION: Underlying hardware implementation must be existing
*
* POST-CONDITION: None
* 
* @param    *server: (IN)structure holding the server
* @return   None
*
* \b Example Example:
* @code
* Network_TCPServer *server = NULL;
* server = (Network_TCPServerInit*)malloc(sizeof(Network_TCPServerInit));
* if(NULL == server){
*       printf("not enough memory\n");
*       //error handler 
* }
* Network_TCPServerInit(server); 
* @endcode
*
* @see Network_TCPServerInit
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void Network_TCPServerInit(Network_TCPServer * server)
{
#if USING_WINC
    server->TCPServer_Open = WINC1500_TCPServerOpen;
    server->TCPServer_Close = WINC1500_TCPServerClose;
    server->TCPServer_Read = WINC1500_TCPServerRead;
    server->TCPServer_Write = WINC1500_TCPServerWrite;
    server->TCPServer_SetCallback = WINC1500_TCPServerSetCallback;
    server->TCPServer_GetStatus = WINC1500_TCPServerGetStatus;
#endif
}

/******************************************************************************
* Function : Network_TCPServerDeInit
*//** 
* \b Description:
*
* This function de-reference the server pointer and free the resource.
*
* PRE-CONDITION: None
*
* POST-CONDITION: None
* 
* @param    *server: (IN)structure holding the server
* @return   None
*
* \b Example Example:
* @code
* Network_TCPServer *server = NULL;
* server = (Network_TCPServerInit*)malloc(sizeof(Network_TCPServerInit));
* if(NULL == server){
*       printf("not enough memory\n");
*       //error handler 
* }
* Network_TCPServerInit(server);
* //Do something
* Network_TCPServerDeInit(server);
* @endcode
*
* @see Network_TCPServerDeInit
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void Network_TCPServerDeInit(Network_TCPServer * server)
{
    server = NULL;
}

	/*** End of File **************************************************************/

