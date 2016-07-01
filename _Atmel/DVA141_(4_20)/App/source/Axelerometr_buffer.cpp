/*
* Axl_buffer.cpp
*
* Created: 01.07.2016 10:46:27
*  Author: drachevam
*/
#include "Axelerometr_buffer.h"



void Axelerometr_buffer::Write(axis_data_t data)
{
	buffer[wr_index++] = data;
	if (wr_index >= AXELEROMETER_BUFFER_SIZE)
	{
		wr_index = 0;
	}
	if (size < AXELEROMETER_BUFFER_SIZE)
	{
		size++;
	}
}

size_t Axelerometr_buffer::Read(axis_data_t* data, size_t data_size)
{
	axis_data_t* current = data;
	taskENTER_CRITICAL();
	axis_data_t* end = current;
	size_t size_data_to_read = data_size > size ? size: data_size;
	end += size_data_to_read;
	uint32_t rd_index = wr_index >= (size) ? wr_index - size: AXELEROMETER_BUFFER_SIZE - (size - wr_index);
	while(current < end)
	{			
		*current = buffer[rd_index++];
		if (rd_index < AXELEROMETER_BUFFER_SIZE)
		{
			rd_index = 0;
		}		
		size--;
		current++;
	}
	taskEXIT_CRITICAL();
	return size_data_to_read;
}

Axelerometr_buffer::Axelerometr_buffer()
{

}

Axelerometr_buffer::~Axelerometr_buffer()
{

}
