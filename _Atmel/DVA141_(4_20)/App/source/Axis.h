/*
* Axis.h
*
* Created: 17.06.2016 14:58:47
*  Author: drachevam
*/


#ifndef AXIS_H_
#define AXIS_H_

#include "os_wrapper.h"
//#include "Vibro_acceleration.h"

#define AXIS_STACK_SIZE (configMINIMAL_STACK_SIZE)

class Axis: public ios_thread
{
	protected:
	
	public:
	Axis(const char* name);
	//Axis(const char* const ThreadName = "Axis", osPriority_t priority =
	//osThreadPriorityNormal, uint32_t stack = 0);
	void main(void);
	//const Vibro_acceleration& A();	
	~Axis(){};
};



#endif /* AXIS_H_ */