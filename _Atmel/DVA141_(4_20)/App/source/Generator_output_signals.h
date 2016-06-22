/*
 * Generator_output_signals.h
 *
 * Created: 09.06.2016 14:43:44
 *  Author: drachevam
 */ 
#include "iSignal.h"

#ifndef GENERATOR_OUTPUT_SIGNALS_H_
#define GENERATOR_OUTPUT_SIGNALS_H_


class Generator_output_signals:public Singleton<Generator_output_signals>
{		
	private:
	
	static void dacConverter(float32_t *src, uint16_t *dst);
	
	public:
		
	static void Output_Amplitude(void *pvParameters);
	static void Output_RMS(void *pvParameters);
	static void Output_PeakToPeak(void *pvParameters);
	
	Generator_output_signals(void);
	virtual ~Generator_output_signals(void);
	};


#endif /* GENERATOR_OUTPUT_SIGNALS_H_ */