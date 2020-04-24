/* 
 * File:   winc1500.h
 * Author: haing
 *
 * Created on April 24, 2020, 2:23 PM
 */

#ifndef WINC1500_H
#define	WINC1500_H

#include "../common.h"
#include "network_conf.h"

uint8_t WINC1500_Init(void);
uint8_t WINC1500_DeInit(void);
uint8_t WINC1500_StartAP(void);
uint8_t WINC1500_StartClient(void);
uint8_t WINC1500_EventHandle(void);


#endif	/* WINC1500_H */

