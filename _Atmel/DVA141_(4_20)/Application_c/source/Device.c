/*
 * Device.c
 *
 * Created: 27.06.2016 15:11:49
 *  Author: drachevam
 */ 

#include "Device.h"

void RunDeviceTask(void *pvParameters);
#define RUN_DEVICE_STACK_SIZE (2*configMINIMAL_STACK_SIZE)


void RunDevice(void )
{	
	xTaskCreate(RunDeviceTask, "RunDevice", RUN_DEVICE_STACK_SIZE, (void *)100, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
}

void RunDeviceTask(void *pvParameters)
{
	for (;;)
	{
		vTaskDelay(100);
	}
	
}