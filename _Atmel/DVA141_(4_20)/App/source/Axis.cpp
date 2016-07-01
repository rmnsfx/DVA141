/*
* Axis.cpp
*
* Created: 17.06.2016 15:01:14
*  Author: drachevam
*/

#include "Axis.h"
#include "Axelerometr_buffer.h"


void Axis::ConvertToVector_q31(axis_data_t* data, size_t datasize, DSP_vector_q31& vector_signal)
{
	float value;
	int32_t size = datasize > vector_signal.size() ? vector_signal.size() : datasize;
	float32_t tmp = 0;
	for (int32_t i = 0; i < size; i++)
	{
		tmp = data->value *0.0039;
		vector_signal[i] = tmp;
	}
}

Axis::Axis(const char* name, Axelerometr_buffer& buffer): ios_thread(name, osThreadPriorityNormal, AXIS_STACK_SIZE),buffer(buffer)
{
	os_wrapper& os = *os_wrapper::getInstance();
	os.threadCreate(this);
}

//Axis::Axis(const char* const ThreadName , osPriority_t priority, uint32_t stack)//: ios_thread(ThreadName,priority,stack)
//{
//
//}



void Axis::main(void)
{
	os_wrapper& os = *os_wrapper::getInstance();
	axis_data_t data[32];
	uint32_t count = 0;
	size_t read_count=0;
	DSP::DSP_vector_q31 vector_data(32);
	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		read_count = buffer.Read((data + count), 32 - count);
		count += read_count;
		if(count == 32)
		{
			/*сконвертировать данные в вектор q31*/
			ConvertToVector_q31(data, 32, vector_data);
			/*отфильтровать данные*/
			/*расчет параметров виброускорения*/
			/*расчет параметров виброскорости*/
			/*расчет параметров виброуперемещения*/
			count = 0;
		}
	}
}

//const Vibro_acceleration& Axis::A()
//{
//static const Vibro_acceleration acc;
//return acc;
//}
//
//Axis::~Axis()
//{

//}
