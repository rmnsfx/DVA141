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
#include "Filter.h"
#include "Vibro_acceleration.h"

//#include "Vibro_acceleration.h"

#define AXIS_STACK_SIZE (3*configMINIMAL_STACK_SIZE)

class Axis: public ios_thread
{
	private:
	void UpSample( q31_t* data, q31_t* vector_signal, size_t size);
	void FastConvertUpSample( axis_data_t* data, q31_t* vector_signal, size_t size_data);
	void Convert_to_acc(float32_t* vector_signal, axis_data_t* data, size_t vector_signal_size);
	Filter filter;
	Vibro_acceleration acceleration;
	protected:
	Axelerometr_buffer& buffer;
	public:
	iSignal& A();
	
	Axis(const char* name, Axelerometr_buffer& buffer);
	//Axis(const char* const ThreadName = "Axis", osPriority_t priority =
	//osThreadPriorityNormal, uint32_t stack = 0);
	void main(void);
	//const Vibro_acceleration& A();	
	~Axis(){};
};



#endif /* AXIS_H_ */