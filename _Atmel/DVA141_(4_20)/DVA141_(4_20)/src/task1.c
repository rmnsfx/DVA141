/*
 * task1.c
 *
 * Created: 08.06.2016 17:00:16
 *  Author: savchenkors
 */ 

#include "task1.h"
#include "AD5421/ad5421.h"
#include "main.h"




volatile uint16_t temp1 = 1;
volatile uint16_t temp2 = 1;

void Testtask(void *pvParameters)
{
	for (;;)
	{
		//ѕила 4-20 мј
		for( int i = 0; i < 65000; i += 5000 )
		{
				
			AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, i);
				
			//temp1 = ADXL345_GetRegisterValue(0x00);				
			temp2 = AD5421_GetTemperature();
				
		}
		
		vTaskDelay(100);
	}
}