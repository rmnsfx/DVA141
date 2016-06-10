#include "Device.h"

#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

static void Testtask(void *pvParameters)
{
	for (;;)
	{
		vTaskDelay(100);
	}
}

void Device::Run()
{
	while (1)
	{
		
		xTaskCreate(Testtask, "Testtask", configMINIMAL_STACK_SIZE, (void *)100, mainQUEUE_SEND_TASK_PRIORITY, NULL);
		vTaskStartScheduler();
	}
}

