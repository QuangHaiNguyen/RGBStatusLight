#include "network_winc1500.h"
#include "../mcc_generated_files/winc/m2m/m2m_wifi.h"
#include "../mcc_generated_files/winc/m2m/m2m_types.h"
#include "../mcc_generated_files/winc/common/winc_defines.h"
#include "../mcc_generated_files/winc/driver/winc_adapter.h"


tstrWifiInitParam wifi_param;

tstrM2MAPConfig apConfig = {
        "WINC_SSID", // Access Point Name.
        1, // Channel to use.
        0, // Wep key index.
        WEP_40_KEY_STRING_SIZE, // Wep key size.
        "1234567890", // Wep key.
        M2M_WIFI_SEC_OPEN, // Security mode.
        SSID_MODE_VISIBLE, // SSID visible.
        {192, 168, 1, 1}
     };

void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg);

uint8_t WINC1500_Init(void)
{
    winc_adapter_init();

    wifi_param.pfAppWifiCb = Wifi_EventCallback;
    
    if( m2m_wifi_init(&wifi_param) != M2M_SUCCESS){
        PRINT_ERROR("%s", "Initialize wifi error\n");
        return -1;
    }
    return 0;
}

uint8_t WINC1500_DeInit(void)
{
    if(m2m_wifi_get_state() == WIFI_STATE_INIT)
        m2m_wifi_deinit(&wifi_param);
    
    return 0;
}

uint8_t WINC1500_StartAP(void)
{
#if 0
    if(m2m_wifi_get_state() != WIFI_STATE_INIT)
    {
        PRINT_ERROR("%s", "Wifi driver is not init\n");
        return -1;
    
#endif
    if( m2m_wifi_start_provision_mode(&apConfig, "atmelwincconfig.com", 1) != M2M_SUCCESS){
        PRINT_ERROR("%s", "AP Provisioning Mode error");
        return -1;
    }
    PRINT_DEBUG("%s", "AP Provisioning mode started\n");
    return 0;
}

uint8_t WINC1500_StartClient(void)
{
    if(m2m_wifi_default_connect() != M2M_SUCCESS){
         PRINT_ERROR("%s", "Cannot connected to an AP\n");
         return -1;
    }
    return 0;
}

uint8_t WINC1500_EventHandle(void)
{
    m2m_wifi_handle_events(NULL);
    return 0;
}


void Wifi_EventCallback(uint8_t u8WiFiEvent, void * pvMsg)
{
    tstrM2MProvisionInfo *pstrProvInfo;
    switch(u8WiFiEvent){
        case M2M_WIFI_RESP_CON_STATE_CHANGED:{
            tstrM2mWifiStateChanged *pstrInfo = (tstrM2mWifiStateChanged*)pvMsg;
            switch(pstrInfo->u8CurrState){
                case M2M_WIFI_CONNECTED:
                    PRINT_DEBUG("%s", "connected\n");
                    m2m_wifi_get_connection_info(); 
                break;
                case M2M_WIFI_DISCONNECTED:
                    PRINT_DEBUG("%s", "disconnected\n");
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
                PRINT_DEBUG("PROV PSK  : %s\n",pstrProvInfo->au8Password);
                m2m_wifi_connect_psk(WIFI_CRED_SAVE_ENCRYPTED, &strNetworkId, &strAuthPsk);
            }
            else{
                PRINT_ERROR("%s", "Provisioning Error\n");
            }
        }
        break;
        
        case M2M_WIFI_REQ_DHCP_CONF: {
            uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
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