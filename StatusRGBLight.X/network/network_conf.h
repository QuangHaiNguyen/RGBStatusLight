/* 
 * File:   network_conf.h
 * Author: haing
 *
 * Created on April 24, 2020, 2:05 PM
 */

#ifndef NETWORK_CONF_H
#define	NETWORK_CONF_H

#define USING_WINC  1

#include "../common.h"

#if USING_WINC
    #include "network_winc1500.h"
    #include "winc1500_tcp_server.h"
#endif


#endif	/* NETWORK_CONF_H */

