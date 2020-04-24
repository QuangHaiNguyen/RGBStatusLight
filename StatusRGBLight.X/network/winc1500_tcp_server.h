/* 
 * File:   tcp_client.h
 * Author: haing
 *
 * Created on April 24, 2020, 10:05 AM
 */

#ifndef TCP_CLIENT_H
#define	TCP_CLIENT_H

#include "network_conf.h"
#include "../mcc_generated_files/winc/m2m/m2m_wifi.h"
#include "../mcc_generated_files/winc/m2m/m2m_types.h"
#include "../mcc_generated_files/winc/common/winc_defines.h"
#include "../mcc_generated_files/winc/driver/winc_adapter.h"

uint8_t WINC1500_TCPServerInit(tpfAppSocketCb socket_cb, uint16_t port_number);
uint8_t WINC1500_TCPServerDeInit(void);
uint8_t WINC1500_TCPServerBind(void);
uint8_t WINC1500_TCPServerClose(void);
uint8_t WINC1500_TCPServerSend(uint8_t *data, uint8_t data_size);
uint8_t WINC1500_TCPServerRecieve(uint8_t * data, uint8_t * size);
uint8_t WINC1500_TCPServerGetIP(uint32_t *ip);

#endif	/* TCP_CLIENT_H */

