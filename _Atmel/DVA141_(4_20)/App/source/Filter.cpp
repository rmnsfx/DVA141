/*
* Filter.cpp
*
* Created: 04.07.2016 15:03:11
*  Author: drachevam
*/

#include "Filter.h"
#include <cmath>

//в знаменателе необходимо инвертировать знаки

//static const float32_t gain[2] = { 0.5107605809916,  0.3729818195101 };
//static const float32_t coef[10] = {1, 2, 1, -0.5654500738938, -0.4775922500725,1, 2, 1, -0.412918704481,  -0.07900857355927} ; 

static const float32_t gain[2] = { 0.6413771412884,  0.6413771412884 };
static const float32_t coef[10] = {1, 0, -1, 1.972233500942, -0.9726187287542, 1, 0, -1, -0.4569532855558, -0.2117293533411} ;

static q31_t coef_q31[10];

Filter::Filter()
{
	float32_t coef_f32 [10];
	int8_t shift = 4;
	uint32_t scale = pow(2, shift);
	for (int i = 0; i < 2; i++)
	{
		 coef_f32[i*5] = coef[i*5] * gain[i] / scale ;
		 coef_f32[i*5 + 1] = coef[i*5 + 1] * gain[i] / scale;
		 coef_f32[i*5 + 2] = coef[i*5 + 2] * gain[i] / scale;
		 coef_f32[i*5 + 3] = coef[i*5 + 3] / scale; 
		 coef_f32[i*5 + 4] = coef[i*5 + 4] / scale;
	}
	arm_float_to_q31(coef_f32, coef_q31, 10);
	for (int i=0; i < 8 ;i++) 
	{ 
		pStates[i] =0;
	}
	arm_biquad_cas_df1_32x64_init_q31(&instatnse_filter, numStages, coef_q31, pStates, shift);
}


void Filter::Filtering(q31_t* destination, q31_t* source, size_t size)
{
	arm_biquad_cas_df1_32x64_q31(&instatnse_filter, source, destination, size);
}

Filter::~Filter()
{

}
