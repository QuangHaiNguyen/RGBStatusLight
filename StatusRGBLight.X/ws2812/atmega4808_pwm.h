/*******************************************************************************
* Title                 :   atmega4808_pwm Component
* Filename              :   atmega4808_pwm.h
* Author                :   Quang Hai Nguyen
* Origin Date           :   20.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** INTERFACE CHANGE LIST *****************************************
*
*  Date         Version     Author              Description 
*  20.04.2020   1.0.0       Quang Hai Nguyen    Interface Created.
*
*******************************************************************************/
/** @file   atmega4808_pwm.h
 *  @brief  This file provides the APIs to interface with TCA timer,
 *          which generate PWM signal for the WS2812 LED strip 
 * 
 *  The Implementation of the TCA timer to generate the the single slope PWM,
 *  which create the pulses to control the WS2812 LED strip.  
 */
#ifndef ATMEGA4808_PWM_H
#define	ATMEGA4808_PWM_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "../common.h"   

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
//Define length for the PWM duty cycle and period
#define BIT_1           6   //6 timer ticks x 100ns = 600ns
#define BIT_0           3   //3 timer ticks x 100ns = 300ns
#define PERIOD          70  //70 timer ticks x 100ns = 7000ns
#define RESET_TIME      3   //3 pulses x 60 timer ticks x 100ns = 18000ns

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void ATMEGA4808_PWM_Init(void);
void ATMEGA4808_PWM_Start(void);
void ATMEGA4808_PWM_Stop(void);
void ATMEGA4808_PWM_DeInit(void);
void ATMEGA4808_PWM_GetRGBDataInfo(uint16_t **ptr_to_buff, uint16_t buff_size);

#endif	/* ATMEGA4808_PWM_H */
/*** End of File **************************************************************/

