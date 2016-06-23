/*
* Task_manager.h
*
* Created: 15.06.2016 10:22:39
*  Author: drachevam
*/


#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <asf.h>
#include "os_wrapper.h"
class Task_manager
{
	private:
	static struct tc_module tc_instance_stat;
	public:
	static inline void Init();
	static uint32_t GetValue();
};



#endif /* TASK_MANAGER_H_ */