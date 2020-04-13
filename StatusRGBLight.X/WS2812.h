/****************************************************************************
* Title                 :   WS2812 Module
* Filename              :   WS2812.h
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
/** @file   WS2812.h
 *  @brief  This file provides the APIs to interface with WS2812 LED Strip 
 * 
 *  The APIs abstract the underlying hardware peripheral, which generates the 
 *  data stream to feed into the LED strip. The users must port the new hardware
 *  or configure the available one.  
 */

#ifndef WS2812_H
#define	WS2812_H


/******************************************************************************
* Includes
*******************************************************************************/
#include "WS2812_conf.h"
#include "mcc_generated_files/mcc.h"
#include "debug.h"

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
//None

/******************************************************************************
* Module Typedefs
*******************************************************************************/
/**
 * List of return statuses
 */
typedef enum WS2812_STATUS{
    WS2812_OK =0,
    WS2812_NOT_MEMORY
}WS2812_Status;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
WS2812_Status WS2812_Init(uint16_t num_of_led, uint16_t **ptr);
WS2812_Status WS2812_DeInit(void);
WS2812_Status WS2812_SetColor(uint16_t position, uint8_t r, uint8_t g, uint8_t b);
WS2812_Status WS2812_SetColorAll(uint8_t r, uint8_t g, uint8_t b);
WS2812_Status WS2812_Update(void);
WS2812_Status WS2812_LedOff(void);

#endif	/* WS2812_H */
/*** End of File **************************************************************/