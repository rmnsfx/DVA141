/*
* Axelerometr.h
*
* Created: 17.06.2016 14:58:12
*  Author: drachevam
*/


#ifndef AXELEROMETR_H_
#define AXELEROMETR_H_
#include "Axis.h"
#include "os_wrapper.h"
#include "Vibro_acceleration.h"
#include "singleton.h"

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


class Axelerometr : public Singleton<Axelerometr>
{
	struct spi_module spi_master_instance_ADXL;
	struct spi_slave_inst slave_ADXL;

	TaskHandle_t x_handle;
	TaskHandle_t y_handle;
	TaskHandle_t z_handle;
	Axelerometr();
	virtual ~Axelerometr();
	void configure_spi_master();
	struct dma_resource example_resource_tx;
	struct dma_resource example_resource_rx;
	void configure_dma_resource_tx();
	void configure_dma_resource_rx();
	DmacDescriptor example_descriptor_tx;
	DmacDescriptor example_descriptor_rx;
	void setup_transfer_descriptor_tx();
	void setup_transfer_descriptor_rx();
	public:
	void StartDMA();
	void StartReadDMA();
	void Start_transfer_DMA();
	void StopDMA();
	void WaitReady(Vibro_acceleration& signal);
	Axis& X();
	Axis& Y();
	Axis& Z();
	protected:
	friend class Singleton<Axelerometr> ;
};


#endif /* AXELEROMETR_H_ */