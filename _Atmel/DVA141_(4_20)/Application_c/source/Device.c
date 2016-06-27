/*
 * Device.c
 *
 * Created: 27.06.2016 15:11:49
 *  Author: drachevam
 */ 

#include "TaskManager.h"
#include "Axelerometer.h"
#include "Device.h"
#include "AD5421.h"

void Testtask(void *pvParameters);
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
	//xTaskCreate(RunDeviceTask, "RunDevice", RUN_DEVICE_STACK_SIZE, (void *)100, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(Testtask, "Test_ad5421", RUN_DEVICE_STACK_SIZE, (void *)100, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
}

void RunDeviceTask(void *pvParameters)
{
	TaskManager_Init();
	Axelerometer_Init();
	for (;;)
	{
		vTaskDelay(100);
	}
	
}

void Testtask(void *pvParameters)
{
	AD5421_Init();
	for (;;)
	{		
		port_pin_set_output_level(PIN_PA24, 1);

		AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, 65535);
		
		port_pin_set_output_level(PIN_PA24, 0);		
		for(int i=0; i<2500; i++) {};
		port_pin_set_output_level(PIN_PA24, 1);		
	
	}
}