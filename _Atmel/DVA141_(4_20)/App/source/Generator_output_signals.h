/*
 * Generator_output_signals.h
 *
 * Created: 09.06.2016 14:43:44
 *  Author: drachevam
 */ 

#include "Axelerometr.h"
#include "iSignal.h"
#include "os_wrapper.h"

#ifndef GENERATOR_OUTPUT_SIGNALS_H_
#define GENERATOR_OUTPUT_SIGNALS_H_


class Generator_output_signals:  public Singleton<Generator_output_signals>, public ios_thread
{		
	private:
	void SetCurrent(uint16_t value);	
	public:

	Generator_output_signals(void);
	virtual ~Generator_output_signals(void);
	
	void main();
	
	static uint32_t dacConverter(q31_t &src);	
	static void outputAmplitude(iSignal &signal);
	static void outputRMS(iSignal &signal);
	static void outputPeakToPeak(iSignal &signal);
	static void loadDAC(void);		
	
	protected:
	friend class Singleton<Generator_output_signals> ;
};


#endif /* GENERATOR_OUTPUT_SIGNALS_H_ */