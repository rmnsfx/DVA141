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
	
	static uint32_t dacConverter(q31_t &src);	
	static void outputAmplitude(iSignal &signal);
	static void outputRMS(iSignal &signal);
	static void outputPeakToPeak(iSignal &signal);
	static void loadDAC(void);
		
	};


#endif /* GENERATOR_OUTPUT_SIGNALS_H_ */