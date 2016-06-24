/*
 * iSignal.cpp
 *
 * Created: 17.06.2016 14:48:01
 *  Author: drachevam
 */ 

#include "iSignal.h"

q31_t iSignal::Amplitude;
q31_t iSignal::RMS;
q31_t iSignal::PeakToPeak;


 iSignal::iSignal(const char* const ThreadName /*= "iSignal"*/, osPriority_t priority /*= osThreadPriorityNormal*/, uint32_t stack /*= 0*/): ios_thread(ThreadName,priority,stack)
{

}

void iSignal::main(void)
{

}

 iSignal::~iSignal()
{

}

void iSignal::getAmplitude(q31_t *inn)
{
	uint32_t pIndex = 0;	
	
	arm_max_q31(inn, sampleSize, &Amplitude, &pIndex);	
}
void iSignal::getPeakToPeak(q31_t *inn)
{
	uint32_t pIndex;	
	q31_t max = 0;
	q31_t min = 0;
	
	arm_max_q31(inn, sampleSize, &max, &pIndex);
	arm_min_q31(inn, sampleSize, &min, &pIndex);	
	
	iSignal::PeakToPeak = max - min;	
}
void iSignal::getRMS(q31_t *inn)
{
	arm_rms_q31(inn, sampleSize, &RMS);	
}