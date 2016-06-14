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

const float32_t pCoeffs [30] = {
	
2147483647,           0,           0,
1386414180,           0,           0,
2147483647, -2147483648,  2135590513,
2147483647,           0, -2147483648,
2147483647,           0,           0,
1386414180,           0,           0,
2147483647,   991564844,   451198350,
2147483647,           0, -2147483648,
2147483647,           0,           0,
2147483647,           0,           0	
	
};

void Sinusoid::Sinus(void *pvParameters)
{
	float32_t param = 80;
	float32_t pSrc[50];
	float32_t pDst[50];
	
	arm_biquad_casd_df1_inst_f32 S;
	uint8_t numStages = 5;	
	float32_t *pStates;
	uint32_t blockSize = 50;
	
		
	
	
	for (;;)
	{
		
		for (int i=0; i<50; i++) pSrc[i] = arm_sin_f32(param*2*PI*i/50);	
		
		arm_biquad_cascade_df1_init_f32(&S, numStages, (float32_t *) &pCoeffs, pStates);
		arm_biquad_cascade_df1_f32(&S, pSrc, pDst, blockSize);		
			
		vTaskDelay(100);
	}
	
	
}