/*******************************************************************************
* Title                 :   atmega4808_rtc Component
* Filename              :   atmega4808_rtc.h
* Author                :   Quang Hai Nguyen
* Origin Date           :   22.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** INTERFACE CHANGE LIST *****************************************
*
*  Date         Version     Author              Description 
*  22.04.2020   1.0.0       Quang Hai Nguyen    Interface Created.
*
*******************************************************************************/
/** @file   atmega4808_rtc.h
 *  @brief  RTC implementation to provide ticks for the scheduler 
 *  
 *  Tick value is updated whenever RTC overflow interrupt is called 
 */
#ifndef ATMEGA4808_RTC_H
#define	ATMEGA4808_RTC_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "../common.h" 

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#define TICK_RETURN     1000000 //in nano second 
#define RTC_PERIOD      (TICK_RETURN/32150) //TICK_RETURN / 32150 ns_per_tick

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
//None

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void ATMEGA4808_RTC_Init(void);
void ATMEGA4808_RTC_DeInit(void);
void ATMEGA4808_RTC_Start(void);
void ATMEGA4808_RTC_Stop(void);
uint32_t ATMEGA4808_RTC_GetTicks(void);
void ATMEGA4808_RTC_SetTicks(uint32_t new_tick);


#endif	/* ATMEGA4808_RTC_H */

