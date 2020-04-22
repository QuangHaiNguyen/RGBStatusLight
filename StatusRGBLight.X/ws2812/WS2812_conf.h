/****************************************************************************
* Title                 :   WS2812 Configure File
* Filename              :   WS2812_conf.h
* Author                :   Quang Hai Nguyen
* Origin Date           :   13.04.2020
* Version               :   0.0.99
*
*****************************************************************************/

/*************** INTERFACE CHANGE LIST **************************************
*
*  Date         Version     Author              Description 
*  13.04.2020   1.0.0       Quang Hai Nguyen    Interface Created.
*
*****************************************************************************/
/** @file   WS2812_conf.h
 *  @brief  This file provides hardware configuration for WS2812 module  
 * 
 * There are many implementations for the WS2812 RGB strip LED, e.g. using bit 
 * banging, SPI or PWM. This file allows the user to choose/add the 
 * implementation on a specific hardware  
 */

#ifndef WS2812_CONF_H
#define	WS2812_CONF_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../common.h"

#define USING_AVR4808       1 

#if USING_AVR4808
    #include "atmega4808_pwm.h"
#endif

   
#ifdef	__cplusplus
}
#endif

#endif	/* WS2812_CONF_H */

