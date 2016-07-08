/*
* TestFilter.cpp
*
* Created: 05.07.2016 10:55:02
*  Author: drachevam
*/

#include "TestFilter.h"
#include "arm_math.h"
#include "Filter.h"

#define TEST_FILTER_STACK_SIZE (6*configMINIMAL_STACK_SIZE)

TestFilter::TestFilter(): ios_thread( "TestFilter", osThreadPriorityNormal, TEST_FILTER_STACK_SIZE)
{

}

TestFilter::~TestFilter()
{

}

#define COUNT_POINT_TEST (100)

void TestFilter::main(void)
{
	float32_t freq = 80;
	uint32_t discret = 1600;
	float32_t sig_f32_befor_1600[COUNT_POINT_TEST/2];
	float32_t sig_f32_befor[COUNT_POINT_TEST];
	float32_t sig_f32_after[COUNT_POINT_TEST];
	q31_t sig_q31[COUNT_POINT_TEST];

	uint32_t index = 0;
	Filter filter;
	float32_t rms_befor;
	float32_t rms_after;
	for (;;)
	{
		for (int i=0; i < COUNT_POINT_TEST/2; i++)
		{
			sig_f32_befor_1600[i] = arm_sin_f32(freq*2*PI*index/discret);
			index++;
		}
		
		for (int i=0; i < COUNT_POINT_TEST; i+=2)
		{
			sig_f32_befor[i] = 0;
			sig_f32_befor[i + 1] = sig_f32_befor_1600[ i / 2 ];  
		}
		arm_rms_f32(sig_f32_befor, COUNT_POINT_TEST , &rms_befor);
		arm_float_to_q31(sig_f32_befor, sig_q31, COUNT_POINT_TEST);
		arm_scale_q31(sig_q31, 0x7FFFFFFF, -6, sig_q31, COUNT_POINT_TEST);	
		filter.Filtering(sig_q31, sig_q31, COUNT_POINT_TEST);
		arm_scale_q31(sig_q31, 0x7FFFFFFF, 7, sig_q31, COUNT_POINT_TEST);	
		arm_q31_to_float(sig_q31, sig_f32_after, COUNT_POINT_TEST);
		arm_rms_f32(sig_f32_after, COUNT_POINT_TEST, &rms_after);
		
	}
}
