/*
 * Sinusoid.cpp
 *
 * Created: 10.06.2016 16:18:43
 *  Author: savchenkors
 */ 

#include "Device.h"
#include "Sinusoid.h"
#include "arm_math.h"


//в знаменателе необходимо инвертировать знаки
const float32_t pCoeffs [10] = {	

0.6413771412884,	 0,					-0.6413771412884,
					 1.972233500942,	-0.9726187287542,

0.6413771412884,	0,					-0.6413771412884,
					-0.4569532855558,	-0.2117293533411,
	
};



void Sinusoid::Sinus(void *pvParameters)
{
	
	float32_t param = 20;
	float32_t pSrc[500];
	float32_t pDst[500];
	
	arm_biquad_casd_df1_inst_f32 S;
	uint8_t numStages = 2;	
	float32_t pStates[8];
	uint32_t blockSize = 500;
	float32_t rmsResult = 0;
	
	
	TickType_t xTimeNow1;
	TickType_t xTimeNow2;
	TickType_t xTimeDiff;
	
	
	for (;;)
	{
		
		for (int i=0; i<500; i++) pSrc[i] = arm_sin_f32(param*2*PI*i/3200);	
		
		arm_rms_f32 (pSrc, blockSize, (float32_t *) &rmsResult);
		arm_biquad_cascade_df1_init_f32(&S, numStages, (float32_t *) &pCoeffs, pStates);
		arm_biquad_cascade_df1_f32(&S, pSrc, pDst, blockSize);		
		
		xTimeNow1 = xTaskGetTickCount();				
		
		arm_biquad_cascade_df1_f32(&S, pSrc, pDst, blockSize);			
		
		xTimeNow2 = xTaskGetTickCount();
		xTimeDiff = (xTimeNow2 - xTimeNow1);
		
		
		arm_rms_f32 (pDst, blockSize, (float32_t *) &rmsResult);
			
		vTaskDelay(100);
	}
	
	
}