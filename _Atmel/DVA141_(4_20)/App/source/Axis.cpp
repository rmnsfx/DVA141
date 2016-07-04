/*
* Axis.cpp
*
* Created: 17.06.2016 15:01:14
*  Author: drachevam
*/

#include "Axis.h"
#include "Axelerometr_buffer.h"

/*конвертирует и пересэмплирует (увеличение дискретизации)*/
void Axis::UpSample( DSP_vector_q31& data, DSP_vector_q31& vector_signal)
{
	float value;
	int32_t size = data.size() > vector_signal.size()/2 ? vector_signal.size()/2 : data.size();
	float32_t tmp = 0;
	for (int32_t i = 0; i < size; i++)
	{
		tmp = data[i] *0.0039;
		vector_signal[2*i] = 0;
		vector_signal[2*i+1] = tmp;
	}
}

/*конвертирует значени€*/
void Axis::Convert_to_acc(axis_data_t* data, size_t datasize, DSP_vector_f32& vector_signal)
{
	float value;
	int32_t size = datasize > vector_signal.size() ? vector_signal.size() : datasize;
	float32_t tmp = 0;
	for (int32_t i = 0; i < size; i++)
	{
		tmp = data->value *0.0039;
		vector_signal[i] = tmp;
		data++;
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

void TestUpsample()
{
	
}

void Axis::main(void)
{
	os_wrapper& os = *os_wrapper::getInstance();
	axis_data_t data[32];
	uint32_t count = 0;
	size_t read_count=0;
	DSP::DSP_vector_f32 value_acc_f32(32);
	DSP::DSP_vector_q31 value_acc_q31(32);
	DSP::DSP_vector_q31 signal(64); //готовый сигнал дл€ вычислени€ значени€ и интегрированию
	DSP::DSP_vector_q31 rms_vector(1);
	size_t max_index;
	size_t min_index;
	q31_t rms;
	float32_t rms_f32_before;
	float32_t rms_f32;
	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		read_count = buffer.Read((data + count), 32 - count);
		count += read_count;
		if(count == 32)
		{
			/*сконвертировать данные в вектор f32*/
			Convert_to_acc(data, 32, value_acc_f32);			
			value_acc_f32.Scale(0.01, value_acc_f32);
			rms_f32_before = value_acc_f32.RMS();
			DSP_converter::f32_to_q31(value_acc_q31, value_acc_f32);			
			
			/*передискретизаци€ данных*/
			UpSample(value_acc_q31, signal);			
			
			/*отфильтровать данные*/
			filter.Filtering(signal, signal);
			
			//signal.Scale(1, signal);
			
			/*умножить значени€ на 2 из-за upsample*/
			//signal.Scale(3, signal);
			
			
			/*расчет параметров виброускорени€*/
			rms = signal.RMS();
			DSP_converter::q31_to_f32(rms_f32, rms);
			/*расчет параметров виброскорости*/
			
			/*расчет параметров виброперемещени€*/
			
			/*расчет параметров векторных сигналов*/
			
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
