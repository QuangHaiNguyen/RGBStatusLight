/*******************************************************************************
* Title                 :   scheduler component   
* Filename              :   scheduler.c
* Author                :   Quang Hai Nguyen
* Origin Date           :   22.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** SOURCE REVISION LOG *****************************************
*
*  Date         Version     Author              Description 
*  22.04.2020   0.0.99       Quang Hai Nguyen    Initial Release.
*
*******************************************************************************/
/** @file  scheduler.c
 *  @brief This is the source file for scheduler component
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "scheduler.h"

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
/** \brief system ticks */
static uint32_t Tick = 0;

/** \brief pointer to the list of the task */
static Task_t *TaskPointer = NULL;

/** \brief index of the list of the tasks */
static uint8_t TaskIndex = 0;

/** \brief number of tasks */
static uint8_t NumTasks = 0;

/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : Scheduler_Init
*//** 
* \b Description:
*
* This function initializes the scheduler and underlying system ticks
*
* PRE-CONDITION: Underlying hardware must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   None
*
* \b Example Example:
* @code
* Scheduler_Init();	
* @endcode
*
* @see Scheduler_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 22.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void Scheduler_Init(void)
{
    
#if ATMEGA4808_RTC
    ATMEGA4808_RTC_Init();
    ATMEGA4808_RTC_Start();
#else
    #warning A hardware must be defined
#endif
	TaskPointer = Task_ConfigGet();    // Get a pointer to the task configuration
    NumTasks = Task_NumTasksGet();		// Number of tasks
    PRINT_DEBUG("%s", "Scheduler is initialized\n");
    PRINT_DEBUG("Number of tasks: %d\n", NumTasks);
}

/******************************************************************************
* Function : Scheduler_Run
*//** 
* \b Description:
*
* This function runs the scheduler
*
* PRE-CONDITION: Scheduler_Init had to be executed
*
* POST-CONDITION: None
* 
* @param    None
* @return   None
*
* \b Example Example:
* @code
* Scheduler_Init();
* while(1){
*     Scheduler_Run();
* } 	
* @endcode
*
* @see Scheduler_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 22.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void Scheduler_Run(void)
{
    
	const uint8_t NumTasks = Task_NumTasksGet();		// Number of tasks

	//assert(TaskPointer != NULL);
	//assert(NumTasks != 0);
#if ATMEGA4808_RTC
	Tick = ATMEGA4808_RTC_GetTicks();		// Get current system tick
#else
    #warning A hardware must be defined
#endif
	/* Loop through the task configuration block and calculate whether there is
	 * a task that is ready to execute. If there is, execute that task. Otherwise
	 * continue looping.
	 */
	for(TaskIndex = 0; TaskIndex < NumTasks; TaskIndex++)
	{
		//assert(TaskIndex < NumTasks);

		if((Tick - TaskPointer[TaskIndex].LastTick) >= TaskPointer[TaskIndex].Interval)
		{
			//assert(TaskPointer[TaskIndex].Func != NULL);

			(*TaskPointer[TaskIndex].Func)();         // Execute Task
			TaskPointer[TaskIndex].LastTick = Tick;  // Save last tick the task was ran.
		}
	}// end for
}
