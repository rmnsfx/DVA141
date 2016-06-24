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

void iSignal::getAmplitude(q31_t inn)
{
	iSignal::Amplitude = inn;
}
void iSignal::getPeakToPeak(q31_t inn)
{
	iSignal::PeakToPeak = inn;
}
void iSignal::getRMS(q31_t inn)
{
	iSignal::RMS = inn;
}