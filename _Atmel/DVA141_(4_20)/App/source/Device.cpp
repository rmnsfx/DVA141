/*
* Device.cpp
*
* Created: 09.06.2016 16:13:25
*  Author: drachevam
*/

#include "Device.h"
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

static void Testtask(void *pvParameters)
{
	bool state;
	for (;;)
	{
		port_pin_set_output_level(PIN_PA27, state);
		state = !state;
		vTaskDelay(100);
	}
}

void Device::Run(void)
{
	system_init();	
	xTaskCreate(Testtask, "Testtask", 2*configMINIMAL_STACK_SIZE, (void *)100, mainQUEUE_SEND_TASK_PRIORITY, NULL);
	vTaskStartScheduler();
}
