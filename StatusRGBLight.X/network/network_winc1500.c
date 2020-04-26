/*******************************************************************************
* Title                 :   winc1500 network component   
* Filename              :   network_winc1500.c
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
/** @file  network_winc1500.c
 *  @brief This is the source file for winc1500 network component
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "network_winc1500.h"
#include "../mcc_generated_files/winc/m2m/m2m_wifi.h"
#include "../mcc_generated_files/winc/m2m/m2m_types.h"
#include "../mcc_generated_files/winc/common/winc_defines.h"
#include "../mcc_generated_files/winc/driver/winc_adapter.h"

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/** \brief structure holds wireless configuration */
tstrWifiInitParam wifi_param;

/** \brief holding the status if the network component*/
Network_Status status = NETWORK_DISCONNECTED;

/** \brief holding the ip address of the device */
uint32_t ip_addr;

tstrM2MAPConfig apConfig = {
        "WINC_SSID",
        1,
        0,                      
        WEP_40_KEY_STRING_SIZE, 
        "1234567890",           
        M2M_WIFI_SEC_OPEN,      
        SSID_MODE_VISIBLE,      
        {192, 168, 1, 1}       
     };

/******************************************************************************
* Function Definitions
*******************************************************************************/
void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg);

/******************************************************************************
* Function : WINC1500_Init
*//** 
* \b Description:
*
* This function initializes the wireless network stack 
*
* PRE-CONDITION: Underlying hardware must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   Network_Status
*
* \b Example Example:
* @code
* WINC1500_Init();
* @endcode
*
* @see WINC1500_Init
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
Network_Status WINC1500_Init(void)
{
    winc_adapter_init();

    wifi_param.pfAppWifiCb = Wifi_EventCallback;
    
    if( m2m_wifi_init(&wifi_param) != M2M_SUCCESS){
        PRINT_ERROR("%s", "Wifi Init error\n");
        return NETWORK_INIT_ERR;
    }
    return NETWORK_OK;
}

/******************************************************************************
* Function : WINC1500_DeInit
*//** 
* \b Description:
*
* This function un-initializes the wireless network stack 
*
* PRE-CONDITION: None
*
* POST-CONDITION: None
* 
* @param    None
* @return   Network_Status
*
* \b Example Example:
* @code
* WINC1500_DeInit();
* @endcode
*
* @see WINC1500_DeInit
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
Network_Status WINC1500_DeInit(void)
{
    if(m2m_wifi_get_state() == WIFI_STATE_INIT)
        m2m_wifi_deinit(&wifi_param);
    
    return NETWORK_OK;
}

/******************************************************************************
* Function : WINC1500_StartAP
*//** 
* \b Description:
*
* This function start the wireless module in access point mode, which is used to 
* provision the ssid and the password to the module
*
* PRE-CONDITION: wireless tack must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   Network_Status
*
* \b Example Example:
* @code
* WINC1500_Init();
* WINC1500_StartAP();
* @endcode
*
* @see WINC1500_Init
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
Network_Status WINC1500_StartAP(void)
{
    if( m2m_wifi_start_provision_mode(&apConfig, "RGBStatus.com", 1) != M2M_SUCCESS){
        PRINT_ERROR("%s", "AP Provisioning Mode error");
        return NETWORK_AP_ERR;
    }
    PRINT_DEBUG("%s", "AP Provisioning mode started\n");
    status = NETWORK_AP_MODE;
    return NETWORK_OK;
}

/******************************************************************************
* Function : WINC1500_StartClient
*//** 
* \b Description:
*
* This function start the wireless module in client mode. It automatically
* connects to the network which is stored in cache of the module. If this 
* function return error, user must run the WINC1500_StartAP to start to 
* provision the device
*
* PRE-CONDITION: wireless tack must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   Network_Status
*
* \b Example Example:
* @code
* WINC1500_Init();
* WINC1500_StartClient();
* @endcode
*
* @see WINC1500_Init
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
Network_Status WINC1500_StartClient(void)
{
    if(m2m_wifi_default_connect() != M2M_SUCCESS){
         PRINT_ERROR("%s", "Cannot connected to an AP\n");
         return NETWORK_CLIENT_CONN_ERR;
    }
    status = NETWORK_CLIENT_MODE;
    return NETWORK_OK;
}

/******************************************************************************
* Function : WINC1500_StopClient
*//** 
* \b Description:
*
* This function disconnect the module from the current network
*
* PRE-CONDITION: wireless tack must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   Network_Status
*
* \b Example Example:
* @code
* if( NETWORK_CONNECTED == WINC1500_GetStatus()){
*       WINC1500_StopClient();
* }
* @endcode
*
* @see WINC1500_Init
* @see WINC1500_GetStatus
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
Network_Status WINC1500_StopClient(void)
{
    m2m_wifi_disconnect();
    status = NETWORK_DISCONNECTED;
    return NETWORK_OK;
}

/******************************************************************************
* Function : WINC1500_StopClient
*//** 
* \b Description:
*
* This function runs the network event handle in the background. It must be 
* called in a loop
*
* PRE-CONDITION: wireless tack must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   Network_Status
*
* \b Example Example:
* @code
* WINC1500_Init();
* WINC1500_StartAP();
* while(1){
*       WINC1500_EventHandle(); 
* } 
* @endcode
*
* @see WINC1500_Init
* @see WINC1500_StartAP
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
Network_Status WINC1500_EventHandle(void)
{
    m2m_wifi_handle_events(NULL);
    return NETWORK_OK;
}

/******************************************************************************
* Function : WINC1500_GetStatus
*//** 
* \b Description:
*
* This function returns the status of the module
*
* PRE-CONDITION: wireless tack must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   Network_Status
*
* \b Example Example:
* @code
* WINC1500_Init();
* WINC1500_StartAP();  
* Network_Status status;
* status = WINC1500_GetStatus();
* @endcode
*
* @see WINC1500_Init
* @see WINC1500_StartAP
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
Network_Status WINC1500_GetStatus(void)
{
    return status;
}

/******************************************************************************
* Function : WINC1500_GetIP
*//** 
* \b Description:
*
* This function returns ip of the module
*
* PRE-CONDITION: wireless tack must be initialized
*
* POST-CONDITION: None
* 
* @param    *ip (OUT)pointer to the ip value
* @return   Network_Status
*
* @see WINC1500_GetIP
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
Network_Status WINC1500_GetIP(uint32_t * ip)
{
    *ip = ip_addr;
    return NETWORK_OK;
}


/******************************************************************************
* Function : Wifi_EventCallback
*//** 
* \b Description:
*
* Callback handles wifi event
*
* PRE-CONDITION: internal use
*
* POST-CONDITION: None
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
void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg)
{
    tstrM2MProvisionInfo *pstrProvInfo;
    switch(u8WiFiEvent){
        case M2M_WIFI_RESP_CON_STATE_CHANGED:{
            tstrM2mWifiStateChanged *pstrInfo = (tstrM2mWifiStateChanged*)pvMsg;
            switch(pstrInfo->u8CurrState){
                case M2M_WIFI_CONNECTED:
                    PRINT_DEBUG("%s", "connected\n");
                    status = NETWORK_CONNECTED;
                    m2m_wifi_get_connection_info(); 
                break;
                case M2M_WIFI_DISCONNECTED:
                    PRINT_DEBUG("%s", "disconnected\n");
                    status = NETWORK_DISCONNECTED;
                    break;
                case M2M_WIFI_ROAMED:
                    PRINT_DEBUG("%s", "roam to new AP\n");
                break;
                case M2M_WIFI_UNDEF:
                    PRINT_DEBUG("%s", "undefined state\n");
                break;
            }
        }
        break;
        
        case M2M_WIFI_RESP_CONN_INFO:{
            tstrM2MConnInfo *pstrInfo = (tstrM2MConnInfo*)pvMsg;
            PRINT_DEBUG("Connected to: %s\n", pstrInfo->acSSID);

        }
        break;
        
        case M2M_WIFI_RESP_PROVISION_INFO:{
            pstrProvInfo = (tstrM2MProvisionInfo*)pvMsg;
            if(pstrProvInfo->u8Status == M2M_SUCCESS){
                tstrNetworkId strNetworkId = {NULL, pstrProvInfo->au8SSID, (uint8_t)strlen((char*)(pstrProvInfo->au8SSID)), M2M_WIFI_CH_ALL};
                tstrAuthPsk strAuthPsk = {NULL, pstrProvInfo->au8Password, (uint8_t)strlen((char*)(pstrProvInfo->au8Password))};
                PRINT_DEBUG("PROV SSID : %s\n",pstrProvInfo->au8SSID);
                if(M2M_SUCCESS != m2m_wifi_connect_psk(WIFI_CRED_SAVE_ENCRYPTED, &strNetworkId, &strAuthPsk)){
                    status = NETWORK_CLIENT_CONN_ERR;
                }
                else{
                    status = NETWORK_CLIENT_MODE;
                }
            }
            else{
                PRINT_ERROR("%s", "Provisioning Error\n");
                status = NETWORK_PROVISION_ERR;
            }
        }
        break;
        
        case M2M_WIFI_REQ_DHCP_CONF: {
            uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
            ip_addr = ((uint32_t)pu8IPAddress[0] << 24) + ((uint32_t)pu8IPAddress[1] << 16) + ((uint32_t)pu8IPAddress[2] << 8) + (uint32_t)pu8IPAddress[3];
            PRINT_DEBUG("WINC1500 IP is %u.%u.%u.%u\r\n",
                    pu8IPAddress[0],
                    pu8IPAddress[1],
                    pu8IPAddress[2],
                    pu8IPAddress[3]);
            } 
        break;
        default:
            PRINT_DEBUG("%s", "Unknown/unhandled wifi event\n");
        break;
    }
}