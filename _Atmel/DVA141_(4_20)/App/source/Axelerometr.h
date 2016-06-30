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
#include "DSP_vector_q31.h"


#define SIZE_ADXL_BUFFER  (32)

typedef struct
{
	uint8_t Samples:5;
	uint8_t Trigger:1;
	uint8_t FIFO_MODE:2;
}fifo_ctl_t;

typedef struct
{
	uint8_t Entries:6;
	uint8_t reserve:1;
	uint8_t FIFO_TRIG:1;
}fifo_status_t;

typedef struct
{
	uint8_t range:2;
	uint8_t Justify:1;
	uint8_t FULL_RES:1;
	uint8_t reserve:1;
	uint8_t INT_INVERT:1;
	uint8_t SPI:1;
	uint8_t SELF_TEST:1;
}data_format_t;

typedef struct
{
	int16_t value:13;
}axis_data_t;

typedef struct
{
	__packed axis_data_t DATAX;
	__packed axis_data_t DATAY;
	__packed axis_data_t DATAZ;
	__packed fifo_ctl_t FIFO_CTL;
	__packed fifo_status_t FIFO_STATUS;
}adxl_data_t;



typedef struct
{
	__packed uint8_t DEVID; // device id
	__packed uint8_t reserve[28];
	__packed uint8_t THRESH_TAP;
	__packed uint8_t OFSX;
	__packed uint8_t OFSY;
	__packed uint8_t OFSZ;
	__packed uint8_t DUR;
	__packed uint8_t Latent;
	__packed uint8_t Window;
	__packed uint8_t THRESH_ACT;
	__packed uint8_t THRESH_INACT;
	__packed uint8_t TIME_INACT;
	__packed uint8_t ACT_INACT_CTL;
	__packed uint8_t THRESH_FF;
	__packed uint8_t TIME_FF;
	__packed uint8_t TAP_AXES;
	__packed uint8_t ACT_TAP_STATUS;
	__packed uint8_t BW_RATE;
	__packed uint8_t POWER_CTL;
	__packed uint8_t INT_ENABLE;
	__packed uint8_t INT_MAP;
	__packed uint8_t INT_SOURCE;
	__packed data_format_t DATA_FORMAT;
	__packed axis_data_t DATAX;
	__packed axis_data_t DATAY;
	__packed axis_data_t DATAZ;
	__packed fifo_ctl_t FIFO_CTL;
	__packed fifo_status_t FIFO_STATUS;
}adxl_registers_t;


typedef enum
{
	DMA_IDLE =0,
	DMA_READ_STATUS,
	DMA_READ_STATUS_EMPTY,
	DMA_READ_DATA,
	DMA_READ_DATA_EMPTY,
	DMA_STOP,
	DMA_READ_ALL_REGISTER_DATA,
}ADXL_DMA_state_t;

typedef union
{
	__packed char data[8];
	__packed struct
	{
		__packed axis_data_t DATAX;
		__packed  axis_data_t DATAY;
		__packed axis_data_t DATAZ;
		__packed fifo_ctl_t FIFO_CTL;
		__packed fifo_status_t FIFO_STATUS;
	};
}data_acceleration_t;


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