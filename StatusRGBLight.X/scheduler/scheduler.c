
#include "scheduler.h"
#include "../debug.h"

static uint32_t Tick = 0;						// System tick
static Task_t *TaskPointer = NULL;         		// Task pointer
static uint8_t TaskIndex = 0;					// Task index
static uint8_t NumTasks = 0;

void Scheduler_Init(void)
{
    PRINT_DEBUG("%s", "Scheduler is initialized\n");
#if ATMEGA4808_RTC
    ATMEGA4808_RTC_Init();
    ATMEGA4808_RTC_Start();
#else
    #warning A hardware must be defined
#endif
	TaskPointer = Task_ConfigGet();    // Get a pointer to the task configuration
    NumTasks = Task_NumTasksGet();		// Number of tasks
    PRINT_DEBUG("Number of tasks: %d\n", NumTasks);
}

void Scheduler_Run(void)
{
    
	const uint8_t NumTasks = Task_NumTasksGet();		// Number of tasks

	//assert(TaskPointer != NULL);
	//assert(NumTasks != 0);

	Tick = ATMEGA4808_RTC_GetTicks();		// Get current system tick

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
