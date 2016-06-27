/*
* Task_manager.cpp
*
* Created: 15.06.2016 10:31:43
*  Author: drachevam
*/
#include "Task_manager.h"

#ifdef __cplusplus
extern "C" {
	#endif
	
	void TaskManagerTimerInit()
	{
		Task_manager::Init();
	}
	
	uint32_t TaskManagerGetValue()
	{
		return Task_manager::GetValue();
	}
	
	#ifdef __cplusplus
}
#endif

struct tc_module Task_manager::tc_instance_stat;

//static struct tc_module tc_instance_stat;

void Task_manager::Init()
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);

	config_tc.counter_size = TC_COUNTER_SIZE_32BIT;
	config_tc.clock_source = GCLK_GENERATOR_1;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	
	tc_init(&tc_instance_stat, TC0, &config_tc);
	tc_set_top_value(&tc_instance_stat,0xFFFFFFFF);
	//! [setup_enable]
	tc_enable(&tc_instance_stat);
}

/*метод для получения времени*/
uint32_t Task_manager::GetValue()
{
	return tc_get_count_value(&tc_instance_stat);
}
