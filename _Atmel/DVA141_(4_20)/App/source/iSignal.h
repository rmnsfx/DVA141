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

class iSignal:public ios_thread
{
	
	protected:
	
	static q31_t Amplitude;
	static q31_t RMS;
	static q31_t PeakToPeak;
	
	public:
			
	iSignal(const char* const ThreadName = "iSignal", osPriority_t priority =
	osThreadPriorityNormal, uint32_t stack = 0);
	void main(void);
	~iSignal();	
	
	static void getAmplitude(q31_t inn);
	static void getPeakToPeak(q31_t inn);
	static void getRMS(q31_t inn);
	
};



#endif /* ISIGNAL_H_ */