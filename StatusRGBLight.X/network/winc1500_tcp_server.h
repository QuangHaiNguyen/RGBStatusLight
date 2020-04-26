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

typedef void (*TCPServer_cb_t)(void);

uint8_t WINC1500_TCPServerOpen( uint16_t port,
                                uint8_t **socket_read_data,
                                uint8_t **socket_write_data,
                                uint16_t socket_data_size,
                                uint32_t *ip);

uint8_t WINC1500_TCPServerClose();
uint8_t WINC1500_TCPServerWrite(uint16_t num_of_byte);
uint8_t WINC1500_TCPServerRead(uint16_t num_of_byte);
uint8_t WINC1500_TCPServerSetCallback(TCPServer_cb_t  cb);

#endif	/* TCP_CLIENT_H */

