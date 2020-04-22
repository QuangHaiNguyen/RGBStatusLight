/* 
 * File:   scheduler_conf.h
 * Author: haing
 *
 * Created on April 22, 2020, 1:28 PM
 */

#ifndef SCHEDULER_CONF_H
#define	SCHEDULER_CONF_H

#include "../mcc_generated_files/mcc.h"

#define ATMEGA4808_RTC 1

#if ATMEGA4808_RTC
    #include "atmega4808_rtc.h"
    #define HW_INTERVAL_1MS     TICK_RETURN/1000000
#else
    #warning A hardware must be defined
#endif


#define INTERVAL_1MS    HW_INTERVAL_1MS
#define INTERVAL_1S     1000 * INTERVAL_1MS


typedef struct
{
  	uint16_t Interval;			/**< Defines how often a task will run  */
  	uint32_t LastTick;			/**< Stores the last tick task was ran  */
  	void (* const Func)(void);			/**< Function pointer to the task  */
}Task_t;

Task_t * const Task_ConfigGet(void);
uint8_t const Task_NumTasksGet(void);



#endif	/* SCHEDULER_CONF_H */

