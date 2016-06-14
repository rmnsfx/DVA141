/*
 * Sinusoid.cpp
 *
 * Created: 10.06.2016 16:18:43
 *  Author: savchenkors
 */ 

#include "Device.h"
#include "Sinusoid.h"
#include "arm_math.h"


#define PI 3.14159265



void Sinusoid::Sinus(void *pvParameters)
{
	float32_t param = 30;
	float32_t pSrc[100];
	float32_t pDst[100];
	
	arm_biquad_casd_df1_inst_f32 *S;
	uint8_t numStages;
	float32_t *pCoeffs;
	float32_t *pStates;
	uint32_t blockSize = 100;
	
	
	for (;;)
	{
		
		for (int i=0; i<100; i++) pSrc[i] = arm_sin_f32(param*2*PI*i/100);	
		
		//arm_biquad_cascade_df1_init_f32(S, numStages, pCoeffs, pStates);
		//arm_biquad_cascade_df1_f32(S, pSrc, pDst, blockSize);
		
			
		vTaskDelay(100);
	}
	
	
}