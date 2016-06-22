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
	public:	
		
	iSignal(const char* const ThreadName = "iSignal", osPriority_t priority =
	osThreadPriorityNormal, uint32_t stack = 0);
	void main(void);
	~iSignal();
	
	static void Amplitude(q31_t *);
	static void PeakToPeak(q31_t *);
	static void RMS(q31_t *);

	
};



#endif /* ISIGNAL_H_ */