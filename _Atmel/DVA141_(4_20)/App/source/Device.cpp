/*
* Device.cpp
*
* Created: 09.06.2016 16:13:25
*  Author: drachevam
*/

#include "Device.h"
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )


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
	for (;;)
	{
		vTaskDelay(100);
	}
}

void Device::Run(void)
{
	system_init();	
	xTaskCreate(DeviceTask, "DeviceTask", 2*configMINIMAL_STACK_SIZE, (void *)100, mainQUEUE_SEND_TASK_PRIORITY, NULL);
	vTaskStartScheduler();
}
