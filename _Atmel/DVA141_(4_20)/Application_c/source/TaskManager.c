/*
* TaskManager.c
*
* Created: 27.06.2016 16:20:12
*  Author: drachevam
*/

#include <asf.h>

#define TASK_MANAGER_STACK_SIZE (10*configMINIMAL_STACK_SIZE)

static struct tc_module tc_instance_stat;

void TaskManagerTimerInit()
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);

	config_tc.counter_size = TC_COUNTER_SIZE_32BIT;
	config_tc.clock_source = GCLK_GENERATOR_0;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	
	tc_init(&tc_instance_stat, TC0, &config_tc);
	tc_set_top_value(&tc_instance_stat,0xFFFFFFFF);
	//! [setup_enable]
	tc_enable(&tc_instance_stat);
}

uint32_t TaskManagerGetValue()
{
	return tc_get_count_value(&tc_instance_stat);
}

uint32_t count_set=0;
char ssst[2048];
char* statsss = ssst;

void TaskManagerTask(void *pvParameters)
{
	for (;;)
	{
		count_set++;
		taskENTER_CRITICAL();
		vTaskGetRunTimeStats(statsss);
		taskEXIT_CRITICAL();
		vTaskDelay(1000);
	}
}

void TaskManager_Init(void)
{
	xTaskCreate(TaskManagerTask, "TaskManager", TASK_MANAGER_STACK_SIZE, (void *)100, tskIDLE_PRIORITY + 1, NULL);
}