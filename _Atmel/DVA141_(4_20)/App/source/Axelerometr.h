/*
* Axelerometr.h
*
* Created: 17.06.2016 14:58:12
*  Author: drachevam
*/


#ifndef AXELEROMETR_H_
#define AXELEROMETR_H_
#include "Axelerometr_types.h"
#include "Axelerometr_buffer.h"
#include "Axis.h"
#include "os_wrapper.h"
#include "Vibro_acceleration.h"
#include "singleton.h"



#define SIZE_ADXL_BUFFER  (32)


class Axelerometr : public Singleton<Axelerometr>, public ios_thread
{
	struct spi_module spi_master_instance_ADXL;
	struct spi_slave_inst slave_ADXL;
	TaskHandle_t x_handle;
	TaskHandle_t y_handle;
	TaskHandle_t z_handle;
	Axelerometr();
	virtual ~Axelerometr();
	void configure_spi_master();
	struct dma_resource adxl_resource_tx;
	struct dma_resource adxl_resource_rx;
	void configure_dma_resource_tx();
	void configure_dma_resource_rx();
	DmacDescriptor adxl_descriptor_tx;
	DmacDescriptor adxl_descriptor_rx;
	/*@param - axis - ось для которой необходимо получить данные
	@param dst - вектор  */
	size_t ReadData(Axis& axis, q31_t& dst);
	public:
	Axelerometr_buffer buffer_x;
	Axelerometr_buffer buffer_y;
	Axelerometr_buffer buffer_z;
	void main();
	void SetDMA_State(ADXL_DMA_state_t state);
	//void WaitReady(Vibro_acceleration& signal);
	Axis& X();
	Axis& Y();
	Axis& Z();
	protected:
	friend class Singleton<Axelerometr> ;
};


#endif /* AXELEROMETR_H_ */