/*
* Generator_output_signals.cpp
*
* Created: 09.06.2016 14:43:33
*  Author: drachevam
*/
#include "Generator_output_signals.h"
#include "Out_4_20.h"

void Generator_output_signals::RMS_signals(void *pvParameters)
{
	Out_4_20 out;
	uint32_t value =0;
	while(1)
	{
		if (value > 24000)
		{
			value =0;
		}
		out.Current(value);
		value += 1000;
		vTaskDelay(10);
	}
}

 Generator_output_signals::Generator_output_signals(void)
{

}
