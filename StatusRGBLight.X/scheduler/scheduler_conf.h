/*******************************************************************************
* Title                 :   scheduler configuration Component
* Filename              :   scheduler_conf.h
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
/** @file   scheduler_conf.h
 *  @brief  Configuration for the scheduler, it is also contains the list of
 *          running tasks
 *  
 */

#ifndef SCHEDULER_CONF_H
#define	SCHEDULER_CONF_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "../common.h"

#define ATMEGA4808_RTC 1

#if ATMEGA4808_RTC
    #include "atmega4808_rtc.h"
#else
    #warning A hardware must be defined
#endif

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#if ATMEGA4808_RTC
    #define HW_INTERVAL_1MS     TICK_RETURN/1000000
#else
    #warning A hardware must be defined
    #define HW_INTERVAL_1MS     1
#endif

#define INTERVAL_1MS    HW_INTERVAL_1MS
#define INTERVAL_1S     1000 * INTERVAL_1MS

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None
typedef struct
{
    /** \brief how often task runs, in milli second */
  	uint16_t Interval;
    /** \brief store the last time task ran */
  	uint32_t LastTick;
    /** \brief pointer to the task function*/
  	void (* const Func)(void);	
}Task_t;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
//None

/******************************************************************************
* Function Prototypes
*******************************************************************************/
Task_t * const Task_ConfigGet(void);
uint8_t const Task_NumTasksGet(void);



#endif	/* SCHEDULER_CONF_H */

