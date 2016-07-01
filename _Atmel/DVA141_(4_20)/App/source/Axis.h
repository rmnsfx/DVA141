/*
* Axis.h
*
* Created: 17.06.2016 14:58:47
*  Author: drachevam
*/


#ifndef AXIS_H_
#define AXIS_H_

#include "os_wrapper.h"
#include "Axelerometr_buffer.h"
#include "DSP_vector_q31.h"
//#include "Vibro_acceleration.h"

#define AXIS_STACK_SIZE (configMINIMAL_STACK_SIZE)

class Axis: public ios_thread
{
	private:
	void ConvertToVector_q31(axis_data_t* data, size_t datasize, DSP_vector_q31& vector_signal);
	protected:
	Axelerometr_buffer& buffer;
	public:
	Axis(const char* name, Axelerometr_buffer& buffer);
	//Axis(const char* const ThreadName = "Axis", osPriority_t priority =
	//osThreadPriorityNormal, uint32_t stack = 0);
	void main(void);
	//const Vibro_acceleration& A();	
	~Axis(){};
};



#endif /* AXIS_H_ */