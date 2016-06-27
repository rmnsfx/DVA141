/*
 * Axelerometer.h
 *
 * Created: 27.06.2016 15:39:06
 *  Author: drachevam
 */ 


#ifndef AXELEROMETER_H_
#define AXELEROMETER_H_

#include "FreeRTOS.h"
#include "task.h"
#include <asf.h>
#include "ADXL346.h"

typedef struct
{
	uint8_t samples:5;
	uint8_t trigger:1;
	uint8_t mode:2;
}fifo_ctl_t;

typedef struct
{
	uint8_t entries:6;
	uint8_t reserve:1;
	uint8_t fifo_trig:1;
}fifo_status_t;

typedef struct
{
	uint16_t value:13;
}axis_data_t;

typedef union
{
	char data[8];
	struct
	{
		axis_data_t DATAX;
		axis_data_t DATAY;
		axis_data_t DATAZ;
		fifo_ctl_t fifo_ctl;
		fifo_status_t fifo_status;
	};
}data_acceleration_t;

void Axelerometer_Init(void);

#endif /* AXELEROMETER_H_ */