/*
* iSignal.h
*
* Created: 17.06.2016 14:38:27
*  Author: drachevam
*/


#ifndef ISIGNAL_H_
#define ISIGNAL_H_

#include "os_wrapper.h"
#include "arm_math.h"

#define sampleSize 64 //кол-во отсчетов в выборке
#define sampleScale 20 //диапазон для масштабирования в q31 и расчета коэф. преобр. в ЦАП

class iSignal
{
	protected:
	volatile q31_t amplitude;
	volatile q31_t rms;
	volatile q31_t peakToPeak;
	
	public:
	
	iSignal();
	
	virtual	~iSignal();
	
	virtual q31_t Amplitude();
	
	virtual q31_t PeakToPeak();
	
	virtual q31_t RMS();
};



#endif /* ISIGNAL_H_ */