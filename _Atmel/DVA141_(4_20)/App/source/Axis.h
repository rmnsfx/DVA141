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

#define AXIS_STACK_SIZE (100)

class Axis: public ios_thread
{
	protected:
	 /* Structure that will hold the TCB of the task being created. */
    StaticTask_t xTaskBuffer;

    /* Buffer that the task being created will use as its stack.  Note this is
    an array of StackType_t variables.  The size of StackType_t is dependent on
    the RTOS port. */
    StackType_t xStack[ AXIS_STACK_SIZE ];
	
	public:
	Axis(const char* name);
	//Axis(const char* const ThreadName = "Axis", osPriority_t priority =
	//osThreadPriorityNormal, uint32_t stack = 0);
	void main(void);
	//const Vibro_acceleration& A();	
	~Axis(){};
};



#endif /* AXIS_H_ */