#include "iSignal.h"


 iSignal::iSignal(const char* const ThreadName /*= "iSignal"*/, osPriority_t priority /*= osThreadPriorityNormal*/, uint32_t stack /*= 0*/): ios_thread(ThreadName,priority,stack)
{

}

/*
 * iSignal.cpp
 *
 * Created: 17.06.2016 14:48:01
 *  Author: drachevam
 */ 

q31_t * Amplitude;
q31_t * RMS;
q31_t * PeakToPeak;

void iSignal::main(void)
{

}

 iSignal::~iSignal()
{

}

void getAmplitude(q31_t * inn)
{
	Amplitude = inn;
}
void getPeakToPeak(q31_t * inn)
{
	PeakToPeak = inn;
}
void getRMS(q31_t * inn)
{
	RMS = inn;
}