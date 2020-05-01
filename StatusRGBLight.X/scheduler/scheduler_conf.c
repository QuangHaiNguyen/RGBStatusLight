/*******************************************************************************
* Title                 :   scheduler configuration Component   
* Filename              :   scheduler_conf.c
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
/** @file  scheduler_conf.c
 *  @brief This is the source file for scheduler_conf component
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "scheduler_conf.h"

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
/** \brief list of tasks the scheduler must run */
static Task_t Tasks[] =
{
	//{ 50* INTERVAL_1MS, 0, Command_Line_Task },
  	//{ 100 * INTERVAL_1MS, 100, Network            },
};

/** \brief number of task the scheduler must run */
static uint8_t const TaskTotalNumber = sizeof(Tasks) / sizeof(*Tasks);


/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : Task_ConfigGet
*//** 
* \b Description:
*
* This function returns the pointer to the task configuration, which is a list
* of task, interval of each task and last time task ran
*
* PRE-CONDITION: None
*
* POST-CONDITION: None
* 
* @param    None
* @return   None
*
* \b Example Example:
* @code
* static Task_t *TaskPointer = NULL; 	
* TaskPointer = Task_ConfigGet();
* @endcode
*
* @see Task_ConfigGet
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
Task_t * const Task_ConfigGet(void)
{
   	return Tasks;
}

/******************************************************************************
* Function : Task_NumTasksGet
*//** 
* \b Description:
*
* This function returns number of tasks
*
* PRE-CONDITION: None
*
* POST-CONDITION: None
* 
* @param    None
* @return   number of tasks scheduler must run
*
* \b Example Example:
* @code
*   static uint8_t num_of_task;
* 	num_of_task = Task_NumTasksGet();
* @endcode
*
* @see Task_NumTasksGet
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
uint8_t const Task_NumTasksGet(void)
{
	return TaskTotalNumber;
}