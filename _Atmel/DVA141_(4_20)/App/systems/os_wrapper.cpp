#include "os_wrapper.h"

extern "C"
{
	static int makeThreadPriority(osPriority_t priority)
	{
		return priority;
	}
	;
}


/*******************************************************************************
* Function:  startScheduler
* Description: Запуск планировщика
* Threading usage and Assumptions:  Все задачи должны быть созданы с помощью
*  taskCreate() до вызова данной функции
******************************************************************************/
void os_wrapper::kernelStart(void)
{
	vTaskStartScheduler();
}

void os_wrapper::Run(void* argument)
{
	const char* const nameThread = ((ios_thread*)argument)->Name();
	/*save thread ID, when trhead exit for main need correct close trhead. */
	os_tid_t tid = ((ios_thread*)argument)->TID();
	//std::cout << "->Start trhead: " << nameThread << tid <<std::endl;
	((ios_thread*)argument)->main();
	//std::cout << "->Stop trhead: " << nameThread << tid << std::endl;
	/*close correct tread*/
	#if (INCLUDE_vTaskDelete == 1)
	vTaskDelete(tid);
	#endif
}

bool os_wrapper::threadCreate(ios_thread *piOsThread)
{
	TaskHandle_t handle;
	/*проверяем наличие задачи*/
	if (piOsThread->tid != NULL)
	{
		return true;
	}
	if (xTaskCreate((TaskFunction_t)os_wrapper::Run, piOsThread->Name(),
	piOsThread->StackSize(), piOsThread, makeThreadPriority(piOsThread->getPriority()),
	&handle) != pdPASS)
	{
		piOsThread->tid = NULL;
		return false;
	}
	piOsThread->tid = handle;
	return true;
}
;

//bool os_wrapper::threadCreate(ios_thread &piOsThread)
//{
//os_wrapper::threadCreate(&piOsThread);
//}

os_tid_t os_wrapper::threadGetCurrentTID()
{
	return 0;
}
;

void os_wrapper::threadTerminate(ios_thread *piOsThread)
{
	#if (INCLUDE_vTaskDelete == 1)
	vTaskDelete(piOsThread->tid);
	#endif
	//std::cout << "Thread Terminate: " << piOsThread->Name() << std::endl;
	piOsThread->tid = NULL;
}
;

void os_wrapper::delay(const uint32_t millisec) const
{
	TickType_t ticks = millisec / portTICK_PERIOD_MS;
	vTaskDelay(ticks ? ticks : 1); /* Minimum delay = 1 tick */
}
;




