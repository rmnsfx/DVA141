/*
 * Axl_buffer.h
 *
 * Created: 01.07.2016 10:46:42
 *  Author: drachevam
 */ 


#ifndef AXL_BUFFER_H_
#define AXL_BUFFER_H_

#include "Axelerometr_types.h"
#define AXELEROMETER_BUFFER_SIZE (64)
class Axelerometr_buffer
{
	axis_data_t buffer[AXELEROMETER_BUFFER_SIZE];
	volatile uint32_t wr_index =0;
	volatile size_t size =0;
	public:
	void Write(axis_data_t data);
	/*метод для считывания данных из буфера
	@parm  data - указатель на массив который необходимо запистаь данные
	@param data_size - размерр масива data*/
	size_t Read(axis_data_t* data, size_t data_size);
	Axelerometr_buffer();
	virtual ~Axelerometr_buffer();
	};



#endif /* AXL_BUFFER_H_ */