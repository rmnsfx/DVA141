/*
* Generator_output_signals.cpp
*
* Created: 09.06.2016 14:43:33
*  Author: drachevam
*/
#include "Generator_output_signals.h"
#include "arm_math.h"
#include "AD5421.h"
#include "iSignal.h"
#include "math.h"


uint8_t result = AD5421::AD5421_Init();


void dacConverter(float32_t * src, uint16_t * dst)
{
	
	//dst = (uint16_t *) ( src / (16 / 65536 - 16384));
	
}


void Generator_output_signals::Output_Amplitude(void *pvParameters)
{	
	uint16_t dacData = 0;
	
	float32_t floatAmplitude = 0.0;
			
	q31_t Amplitude = 0;
	
	iSignal::Amplitude(&Amplitude);
	
	arm_q31_to_float(&Amplitude, &floatAmplitude, 1);
	
	dacConverter(&floatAmplitude, &dacData); 
	
	AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);		
	
}


void Generator_output_signals::Output_RMS(void *pvParameters)
{
	uint16_t dacData = 0;	
	
	float32_t floatRMS = 0.0;
	
	q31_t RMS = 0;
	
	iSignal::RMS(&RMS);
	
	arm_q31_to_float(&RMS, &floatRMS, 1);	
	
	dacConverter(&floatRMS, &dacData);
		
	AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
}

void Generator_output_signals::Output_PeakToPeak(void *pvParameters)
{
	uint16_t dacData = 0;	
	
	float32_t floatPeakToPeak = 0.0;	
	
	q31_t PeakToPeak = 0;
	
	iSignal::PeakToPeak(&PeakToPeak);
	
	arm_q31_to_float(&PeakToPeak, &floatPeakToPeak, 1);
	
	dacConverter(&floatPeakToPeak, &dacData);
	
	AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
}