/*
* Generator_output_signals.cpp
*
* Created: 09.06.2016 14:43:33
*  Author: drachevam
*/
#include "Generator_output_signals.h"
#include "arm_math.h"
#include "AD5421.h"



uint32_t Generator_output_signals::dacConverter(q31_t src)
{	
	float32_t temp = 0.0;	
	float32_t temp2 = 0.0;	
		
	arm_q31_to_float(&src, &temp,1);
	
	temp2 = 16 / (float32_t) (65536 - 16384);
	
	return (uint32_t) ( temp / temp2 );	
}


void Generator_output_signals::Output_Amplitude(iSignal signal)
{	
	
	uint32_t dacData = 0;	
	
	uint8_t result = AD5421::AD5421_Init();
	
	for( ;; )
	{
				
		dacData = Generator_output_signals::dacConverter(signal.Amplitude);
		
		dacData*= 100;
		
		AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
		
	}
	
}


void Generator_output_signals::Output_RMS(iSignal signal)
{
	uint32_t dacData = 0;	
	
	q31_t RMS = 0;
	
	uint8_t result = AD5421::AD5421_Init();
	
	for( ;; )
	{				
		dacData = Generator_output_signals::dacConverter(signal.RMS);
		
		AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
		
	}
	
}



void Generator_output_signals::Output_PeakToPeak(iSignal signal)
{
	uint32_t dacData = 0;
	
	q31_t PeakToPeak = 0;
	
	uint8_t result = AD5421::AD5421_Init();
	
	for( ;; )
	{
		dacData = Generator_output_signals::dacConverter(signal.PeakToPeak);
		
		AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
	}
}