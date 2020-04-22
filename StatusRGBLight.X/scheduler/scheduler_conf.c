#include "scheduler_conf.h"
#include "Test_Task_1s.h"
#include "Test_Task_2s.h"

static Task_t Tasks[] =
{
	{ INTERVAL_1S,        0, Task_1s       },
  	{ 2*INTERVAL_1S,      0, Task_2s      },
  	//{ INTERVAL_BACKGROUND, 0, Task_Background },
};

static uint8_t const TaskTotalNumber = sizeof(Tasks) / sizeof(*Tasks);

Task_t * const Task_ConfigGet(void)
{
   	return Tasks;
}

uint8_t const Task_NumTasksGet(void)
{
	return TaskTotalNumber;
}