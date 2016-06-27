/*
 * Device.c
 *
 * Created: 27.06.2016 15:11:49
 *  Author: drachevam
 */ 

#include "Axelerometer.h"
#include "Device.h"


void RunDeviceTask(void *pvParameters);
#define RUN_DEVICE_STACK_SIZE (2*configMINIMAL_STACK_SIZE)

	/*функции для работы вывода printf*/
	int _write(int file, char *ptr, int len)
	{
		return len;
	}
	
	/*функции для работы ввода scanf*/
	int _read(int file, char *ptr, int len)
	{
		return 0;
	}


void RunDevice(void )
{	
	xTaskCreate(RunDeviceTask, "RunDevice", RUN_DEVICE_STACK_SIZE, (void *)100, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
}

void RunDeviceTask(void *pvParameters)
{
	Axelerometer_Init();
	for (;;)
	{
		vTaskDelay(100);
	}
	
}