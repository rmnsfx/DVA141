/*
 * Filter.h
 *
 * Created: 04.07.2016 15:03:01
 *  Author: drachevam
 */ 


#ifndef FILTER_H_
#define FILTER_H_

#include "arm_math.h"

class Filter
{
	static const uint8_t numStages = 2; 
	//в знаменателе необходимо инвертировать знаки
	static const float32_t pCoeffs[10] ;
	
	arm_biquad_cas_df1_32x64_ins_q31 instatnse_filter;

	q63_t pStates[8];
	protected:
	 
	public:		
		Filter();
		void Filtering(q31_t* destination, q31_t* source, size_t size);
		virtual ~Filter();
	};




#endif /* FILTER_H_ */