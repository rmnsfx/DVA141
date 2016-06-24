/*
 * Generator_output_signals.h
 *
 * Created: 09.06.2016 14:43:44
 *  Author: drachevam
 */ 
#include "iSignal.h"

#ifndef GENERATOR_OUTPUT_SIGNALS_H_
#define GENERATOR_OUTPUT_SIGNALS_H_


class Generator_output_signals:public iSignal
{		
	private:
	
	
	
	public:

	Generator_output_signals(void);
	virtual ~Generator_output_signals(void);
	
	static uint32_t dacConverter(q31_t src);	
	static void Output_Amplitude(iSignal signal);
	static void Output_RMS(iSignal signal);
	static void Output_PeakToPeak(iSignal signal);
		
	};


#endif /* GENERATOR_OUTPUT_SIGNALS_H_ */