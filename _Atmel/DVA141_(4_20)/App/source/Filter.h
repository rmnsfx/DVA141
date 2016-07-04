/*
 * Filter.h
 *
 * Created: 04.07.2016 15:03:01
 *  Author: drachevam
 */ 


#ifndef FILTER_H_
#define FILTER_H_

#include "arm_math.h"
#include "DSP_vector_q31.h"

class Filter
{
	static const uint8_t numStages = 2; 
	//в знаменателе необходимо инвертировать знаки
	static const float32_t pCoeffs[10] ;
	
	arm_biquad_cas_df1_32x64_ins_q31 instatnse_filter;
	q63_t pStates[8];
	public:
		Filter();
		void Filtering(DSP_vector_q31& destination, DSP_vector_q31& source);
		virtual ~Filter();
	};




#endif /* FILTER_H_ */