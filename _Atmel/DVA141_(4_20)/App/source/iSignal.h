/*
* iSignal.h
*
* Created: 17.06.2016 14:38:27
*  Author: drachevam
*/


#ifndef ISIGNAL_H_
#define ISIGNAL_H_

#include "os_wrapper.h"

class iSignal:public ios_thread
{
	public:
	iSignal(const char* const ThreadName = "iSignal", osPriority_t priority =
	osThreadPriorityNormal, uint32_t stack = 0);
	void main(void);
	~iSignal();
};



#endif /* ISIGNAL_H_ */