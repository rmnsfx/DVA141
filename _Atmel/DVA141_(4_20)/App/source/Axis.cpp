/*
* Axis.cpp
*
* Created: 17.06.2016 15:01:14
*  Author: drachevam
*/

#include "Axis.h"
#include "Axelerometr_buffer.h"

/*������������ � �������������� (���������� �������������)*/
void Axis::UpSample( q31_t* data, q31_t* vector_signal, size_t size)
{
	float value;	
	float32_t tmp = 0;
	for (int32_t i = 0; i < size; i++)
	{
		tmp = data[i] *0.0039;
		vector_signal[2*i] = 0;
		vector_signal[2*i + 1] = tmp;
	}
}

/*������������ ��������*/
void Axis::Convert_to_acc(float32_t* vector_signal, axis_data_t* data, size_t vector_signal_size)
{
	float32_t tmp = 0;
	for (int32_t i = 0; i < vector_signal_size; i++)
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

#define COUNT_POINT_TO_CALCULATE (32)  /*���������� ����� ��� �������*/

void Axis::main(void)
{
	os_wrapper& os = *os_wrapper::getInstance();
	axis_data_t data[COUNT_POINT_TO_CALCULATE];
	float32_t value_acc_f32[COUNT_POINT_TO_CALCULATE];
	q31_t value_acc_q31[COUNT_POINT_TO_CALCULATE];
	q31_t signal[2*COUNT_POINT_TO_CALCULATE]; //������� ������ ��� ���������� �������� � ��������������

	uint32_t count = 0;
	size_t read_count = 0;
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
			/*��������������� ������ � ������ f32*/
			Convert_to_acc(value_acc_f32, data, COUNT_POINT_TO_CALCULATE);	
			arm_scale_f32(value_acc_f32, 0.01,value_acc_f32,COUNT_POINT_TO_CALCULATE);		
			arm_rms_f32(value_acc_f32, COUNT_POINT_TO_CALCULATE, &rms_f32_before);
			arm_float_to_q31(value_acc_f32, value_acc_q31, COUNT_POINT_TO_CALCULATE);
				
			/*����������������� ������*/
			UpSample(value_acc_q31, signal, COUNT_POINT_TO_CALCULATE);			
			
			/*������������� ������*/
			filter.Filtering(signal, signal, 2*COUNT_POINT_TO_CALCULATE);
			
			//signal.Scale(1, signal);
			
			/*�������� �������� �� 2 ��-�� upsample*/
			//signal.Scale(3, signal);
			
			
			/*������ ���������� ��������������*/
			arm_rms_q31(signal, 2*COUNT_POINT_TO_CALCULATE, &rms);
			arm_q31_to_float(&rms, &rms_f32, 1);
			/*������ ���������� �������������*/
			
			/*������ ���������� ����������������*/
			
			/*������ ���������� ��������� ��������*/
			
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
