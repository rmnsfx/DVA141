/*
* Filter.cpp
*
* Created: 04.07.2016 15:03:11
*  Author: drachevam
*/

#include "Filter.h"

//в знаменателе необходимо инвертировать знаки
const float32_t Filter::pCoeffs[10] = {

	0.6413771412884,	 0,					-0.6413771412884,
	1.972233500942,	-0.9726187287542,

	0.6413771412884,	0,					-0.6413771412884,
	-0.4569532855558,	-0.2117293533411,
};

Filter::Filter()
{
	float32_t coef_f32 [10];
	q31_t coef_q31[10];
	for (int i = 0; i < 10; i++) coef_f32[i] = pCoeffs[i] / 2;
	arm_float_to_q31(coef_f32, coef_q31, 10);
	arm_biquad_cas_df1_32x64_init_q31(&instatnse_filter, numStages, (q31_t *) &coef_q31, pStates, 1);
}

void Filter::Filtering(DSP_vector_q31& destination, DSP_vector_q31& source)
{
	uint32_t size = source.size() > destination.size() ? destination.size() : source.size();
	arm_biquad_cas_df1_32x64_q31(&instatnse_filter, &source[0], &destination[0], size);
}

Filter::~Filter()
{

}
