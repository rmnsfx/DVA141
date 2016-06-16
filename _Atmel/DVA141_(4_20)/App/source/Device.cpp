/*
* Device.cpp
*
* Created: 09.06.2016 16:13:25
*  Author: drachevam
*/

#include "Device.h"
#include "stdio.h"
#include "Task_manager.h"
#include "Sinusoid.h"

#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

#ifdef __cplusplus
extern "C"
{
	#endif

	/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
	implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
	used by the Idle task. */
	void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
	StackType_t **ppxIdleTaskStackBuffer,
	uint32_t *pulIdleTaskStackSize )
	{
		/* If the buffers to be provided to the Idle task are declared inside this
		function then they must be declared static - otherwise they will be allocated on
		the stack and so not exists after this function exits. */
		static StaticTask_t xIdleTaskTCB;
		static StackType_t uxIdleTaskStack[ 2*configMINIMAL_STACK_SIZE ];

		/* Pass out a pointer to the StaticTask_t structure in which the Idle task's
		state will be stored. */
		*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

		/* Pass out the array that will be used as the Idle task's stack. */
		*ppxIdleTaskStackBuffer = uxIdleTaskStack;

		/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
		Note that, as the array is necessarily of type StackType_t,
		configMINIMAL_STACK_SIZE is specified in words, not bytes. */
		*pulIdleTaskStackSize = 2*configMINIMAL_STACK_SIZE;
	}
	/*-----------------------------------------------------------*/

	/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
	application must provide an implementation of vApplicationGetTimerTaskMemory()
	to provide the memory that is used by the Timer service task. */
	void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
	StackType_t **ppxTimerTaskStackBuffer,
	uint32_t *pulTimerTaskStackSize )
	{
		/* If the buffers to be provided to the Timer task are declared inside this
		function then they must be declared static - otherwise they will be allocated on
		the stack and so not exists after this function exits. */
		static StaticTask_t xTimerTaskTCB;
		static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

		/* Pass out a pointer to the StaticTask_t structure in which the Timer
		task's state will be stored. */
		*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

		/* Pass out the array that will be used as the Timer task's stack. */
		*ppxTimerTaskStackBuffer = uxTimerTaskStack;

		/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
		Note that, as the array is necessarily of type StackType_t,
		configMINIMAL_STACK_SIZE is specified in words, not bytes. */
		*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
	}

	#ifdef __cplusplus
}
#endif

void *operator new(size_t size)
{
	void* mem = pvPortMalloc(size);
	#ifdef DEBUG_PROJ
	printf("new memory =%x; size=%d; Heap=%d;\r\n", mem, size,
	xPortGetFreeHeapSize());
	if (mem == NULL)
	{
		printf("failed to allocate memory. Heap=%d; need=%d; \r\n",
		xPortGetFreeHeapSize(), size);
		while (1)
		{
		};
	}
	#endif
	return mem;
}

void operator delete(void *p)
{
	#ifdef DEBUG_PROJ
	printf("delet memory %x; Heap=%d;\r\n", p, xPortGetFreeHeapSize());
	if (p == NULL)
	{
		printf("failed to remove memory NULL pointer");
	}
	#endif
	vPortFree(p);
}

void *operator new[](size_t size)
{
	void* mem = pvPortMalloc(size);
	#ifdef DEBUG_PROJ
	printf("new memory for massive =%x; size=%d; Heap=%d;\r\n", mem, size,
	xPortGetFreeHeapSize());
	if (mem == NULL)
	{
		printf("failed to allocate memory for massive. Heap=%d; need=%d; \r\n",
		xPortGetFreeHeapSize(), size);
		while (1)
		{
		};
	}
	#endif
	return mem;
}

void operator delete[](void *p)
{
	#ifdef DEBUG_PROJ
	printf("delet memory for massive  %x; Heap=%d; \r\n", p,
	xPortGetFreeHeapSize());
	if (p == NULL)
	{
		printf("failed to remove memory for massive NULL pointer");
	}
	#endif
	vPortFree(p);
}

void Device::DeviceTask(void *pvParameters)
{
	const char* name = (const char*)pvParameters;
	uint32_t tick;
	for (;;)
	{
		tick=Task_manager::GetValue();
		vTaskDelay(10);
	}
}


void Device::RunTimeStatsTask(void *pvParameters)
{
 char* stat = new char[2024];
	for (;;)
	{
		vTaskGetRunTimeStats(stat);
		vTaskDelay(1000);
	}
}

void Device::Run(void)
{
	system_init();
	
	//xTaskCreate(DeviceTask, "DeviceTask", 2*configMINIMAL_STACK_SIZE, (void *)"Task1", mainQUEUE_SEND_TASK_PRIORITY, NULL);	
	//xTaskCreate(DeviceTask, "DeviceTask2", 2*configMINIMAL_STACK_SIZE, (void *)"Task2", mainQUEUE_SEND_TASK_PRIORITY, NULL);
	//xTaskCreate(Sinusoid::Sinus, "SinusTask", 30*configMINIMAL_STACK_SIZE, (void *)100, 2, NULL);	
	xTaskCreate(RunTimeStatsTask, "RunTimeStat", 3*configMINIMAL_STACK_SIZE, (void *)"RunTimeStat", mainQUEUE_SEND_TASK_PRIORITY, NULL);
	xTaskCreate(Sinusoid::Sinus_double, "SinusTask2", 33*configMINIMAL_STACK_SIZE, (void *)100, 2, NULL);
	vTaskStartScheduler();
}
