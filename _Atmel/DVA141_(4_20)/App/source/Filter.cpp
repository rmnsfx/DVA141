/*
* Filter.cpp
*
* Created: 04.07.2016 15:03:11
*  Author: drachevam
*/

#include "Filter.h"
#include <cmath>

//� ����������� ���������� ������������� �����


///*��������� ������ ����������� 4-�� �������
//������� ������������� 1600, �������� ������ 10 - 1000 ��*/
//static const float32_t gain[2] = { 0.6455994115838,  0.6455994115838 };
//static const float32_t coef[10] = {1, 0, -1, 1.994446408396, -0.9944618272816, 1, 0, -1, -0.4617333616139, -0.2101056045648} ;

///*��������� ������ ����������� 4-�� �������
//������� ������������� 3200, �������� ������ 10 - 500 ��*/
static const float32_t gain[2] = { 0.3681040389081,  0.3681040389081 };
static const float32_t coef[10] = {1, 0, -1, 1.972257971499, -0.9726521517106, 1, 0, -1, 0.723035696116, -0.2732050948352} ;

///*��������� ������ ����������� 4-�� �������
//������� ������������� 3200, �������� ������ 2 - 1000 ��*/
//static const float32_t gain[2] = { 0.6455994115838,  0.6455994115838 };
//static const float32_t coef[10] = {1, 0, -1, 1.994446408396, -0.9944618272816, 1, 0, -1, -0.4617333616139, -0.2101056045648} ;
//
///*��������� ������ ����������� 4-�� �������
//������� ������������� 3200, �������� ������ 5 - 1000 ��*/
//static const float32_t gain[2] = { 0.6440156726262,  0.6440156726262 };
//static const float32_t coef[10] = {1, 0, -1, 1.986116179896, -0.9862125253785, 1, 0, -1, -0.4599334761773, -0.2107026857067} ;

/*������� ������������� 3200, ��������� ������ 10 - 1000 ��*/
//static const float32_t gain[2] = { 0.6413771412884,  0.6413771412884 };
//static const float32_t coef[10] = {1, 0, -1, 1.972233500942, -0.9726187287542, 1, 0, -1, -0.4569532855558, -0.2117293533411} ;



static q31_t coef_q31[10];

Filter::Filter()
{
	float32_t coef_f32 [10];
	int8_t shift = log2(DEVIDER_RATIO);
	uint32_t scale = pow(2, shift);
	for (int i = 0; i < 2; i++)
	{
		 coef_f32[i*5] = coef[i*5] * gain[i] / scale;
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