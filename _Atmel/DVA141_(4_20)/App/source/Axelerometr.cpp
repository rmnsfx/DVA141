/*
* Axelerometr.cpp
*
* Created: 17.06.2016 15:03:23
*  Author: drachevam
*/
#include "Axelerometr.h"
#include "ADXL346.h"

struct spi_module* spi_master_instance_ADXL_pointer;

#ifdef __cplusplus
extern "C" {
	#endif
	void SPI_Write_ADXL(uint8_t* data)
	{
		port_pin_set_output_level(PIN_PA06, 0);
		spi_write_buffer_wait(spi_master_instance_ADXL_pointer, data, 2);
		port_pin_set_output_level(PIN_PA06, 1);
	}

	void SPI_Read_ADXL(uint8_t* data)
	{
		port_pin_set_output_level(PIN_PA06, 0);
		//spi_read_buffer_wait(&spi_master_instance_ADXL, data, 2, 0);
		spi_transceive_buffer_wait(spi_master_instance_ADXL_pointer, data, data, 2);
		port_pin_set_output_level(PIN_PA06, 1);
	}
	#ifdef __cplusplus
}
#endif

//[definition_master]
#define CONF_MASTER_SPI_MODULE  SERCOM0
#define CONF_MASTER_SS_PIN      PIN_PA06
#define CONF_MASTER_MUX_SETTING SPI_SIGNAL_MUX_SETTING_E
#define CONF_MASTER_PINMUX_PAD0 PINMUX_PA04D_SERCOM0_PAD0
#define CONF_MASTER_PINMUX_PAD1 PINMUX_PA05D_SERCOM0_PAD1
#define CONF_MASTER_PINMUX_PAD2 PINMUX_UNUSED
#define CONF_MASTER_PINMUX_PAD3 PINMUX_PA07D_SERCOM0_PAD3

#define CONF_PERIPHERAL_TRIGGER_TX   SERCOM0_DMAC_ID_TX
#define CONF_PERIPHERAL_TRIGGER_RX   SERCOM0_DMAC_ID_RX


//! [slave_select_pin]
#define SLAVE_SELECT_PIN CONF_MASTER_SS_PIN

Axelerometr* Axel;
//! [spi_buffer]
static  uint8_t buffer_tx[8] = {
	ADXL345_SPI_READ | ADXL345_SPI_MB | ADXL345_DATAX0  , 0x00
};

////! [spi_buffer]
//static  uint8_t buffer_rx[8] = {
//0x00 , 0x00,0x00,0x00,0x00,0x00,
//};

__packed data_acceleration_t buffer_read;

static volatile bool ReadData = false;

static void transfer_tx_done(struct dma_resource* const resource )
{
	//uint8_t* data_tx = buffer_tx;
	//uint8_t* data_rx =	buffer_rx;
	//*data_tx = *data_tx;
	//*data_rx = *data_rx;
	Axel->StopDMA();
}

static void transfer_rx_done(struct dma_resource* const resource )
{
	static uint32_t count =0;
	if (buffer_read.fifo_status.entries >0)
	{
		count++;
		for(int i =0; i< 24000;)
		{
			i++;
		}
		Axel->StartDMA();
	}
	else
	{
		Axel->StopDMA();
		count=0;
	}
	
	
	//if (ReadData == false)
	//{
		//ReadData= true;
		//Axel->StartDMA();
	//}
	//else
	//{
		//ReadData = false;
		//if (buffer_read.fifo_status.entries >0)
		//{
			//count++;
			//Axel->StopDMA();
			//Axel->Start_transfer_DMA();
		//}
		//else
		//{
			//Axel->StopDMA();
			//count=0;
		//}
	//}
}


Axelerometr::Axelerometr()
{
	x_handle = NULL;
	y_handle = NULL;
	z_handle = NULL;
	
	configure_spi_master();

	Axel = this;
	uint16_t ax,ay,az,t;
	char val;
	
	{
		ax = ADXL345_GetX();
		ay = ADXL345_GetY();
		az = ADXL345_GetZ();
		t++;
		val = ADXL345_GetRegisterValue(ADXL345_DEVID);
		val = ADXL345_GetRegisterValue(ADXL345_BW_RATE);
		val++;
	}

	configure_dma_resource_tx();
	configure_dma_resource_rx();
	setup_transfer_descriptor_tx();
	setup_transfer_descriptor_rx();
	dma_add_descriptor(&example_resource_tx, &example_descriptor_tx);
	dma_add_descriptor(&example_resource_rx, &example_descriptor_rx);
	dma_register_callback(&example_resource_tx, transfer_tx_done, DMA_CALLBACK_TRANSFER_DONE);
	dma_register_callback(&example_resource_rx, transfer_rx_done, DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&example_resource_rx, DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&example_resource_tx, DMA_CALLBACK_TRANSFER_DONE);

	
	//configure_dma_resource_tx(&example_resource_tx);
	//configure_dma_resource_rx(&example_resource_rx);
	//setup_transfer_descriptor_tx(&example_descriptor_tx);
	//setup_transfer_descriptor_rx(&example_descriptor_rx);
	//dma_add_descriptor(&example_resource_tx, &example_descriptor_tx);
	//dma_add_descriptor(&example_resource_rx, &example_descriptor_rx);
	//dma_register_callback(&example_resource_tx, transfer_tx_done,	DMA_CALLBACK_TRANSFER_DONE);
	//dma_register_callback(&example_resource_rx, transfer_rx_done,	DMA_CALLBACK_TRANSFER_DONE);
}

Axelerometr::~Axelerometr()
{

}

void Axelerometr::configure_spi_master()
{
	spi_master_instance_ADXL_pointer = &spi_master_instance_ADXL;
	/*������������� SPI*/
	struct spi_config config_spi_master_adxl;

	struct spi_slave_inst_config slave_dev_config_adxl;

	spi_slave_inst_get_config_defaults(&slave_dev_config_adxl);

	slave_dev_config_adxl.ss_pin = SLAVE_SELECT_PIN;
	slave_dev_config_adxl.address_enabled = false;

	spi_attach_slave(&slave_ADXL, &slave_dev_config_adxl);

	spi_get_config_defaults(&config_spi_master_adxl);

	config_spi_master_adxl.mux_setting = SPI_SIGNAL_MUX_SETTING_D;
	config_spi_master_adxl.pinmux_pad0 = CONF_MASTER_PINMUX_PAD0;
	config_spi_master_adxl.pinmux_pad1 = CONF_MASTER_PINMUX_PAD1;
	config_spi_master_adxl.pinmux_pad2 = CONF_MASTER_PINMUX_PAD2;
	config_spi_master_adxl.pinmux_pad3 = CONF_MASTER_PINMUX_PAD3;
	
	config_spi_master_adxl.mode             = SPI_MODE_MASTER;
	config_spi_master_adxl.data_order       = SPI_DATA_ORDER_MSB;
	config_spi_master_adxl.transfer_mode    = SPI_TRANSFER_MODE_3;
	config_spi_master_adxl.character_size   = SPI_CHARACTER_SIZE_8BIT;
	config_spi_master_adxl.run_in_standby   = false;
	config_spi_master_adxl.receiver_enable  = true;
	config_spi_master_adxl.generator_source = GCLK_GENERATOR_0;
	config_spi_master_adxl.mode_specific.master.baudrate = 4000000;
	//config_spi_master_adxl.master_slave_select_enable = true;
	config_spi_master_adxl.select_slave_low_detect_enable = false;

	spi_init(&spi_master_instance_ADXL, SERCOM0, &config_spi_master_adxl);

	spi_enable(&spi_master_instance_ADXL);

	ADXL345_Init();
}


void Axelerometr::configure_dma_resource_tx()
{
	struct dma_resource *tx_resource = &example_resource_tx;
	//! [dma_tx_setup_1]
	struct dma_resource_config tx_config;
	//! [dma_tx_setup_1]

	//! [dma_tx_setup_2]
	dma_get_config_defaults(&tx_config);
	//! [dma_tx_setup_2]

	//! [dma_tx_setup_3]
	tx_config.peripheral_trigger = CONF_PERIPHERAL_TRIGGER_TX;
	tx_config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	//! [dma_tx_setup_3]

	//! [dma_tx_setup_4]
	dma_allocate(tx_resource, &tx_config);
	//! [dma_tx_setup_4]
}

void Axelerometr::configure_dma_resource_rx()
{
	struct dma_resource *rx_resource = &example_resource_rx;
	//! [dma_rx_setup_1]
	struct dma_resource_config rx_config;
	//! [dma_rx_setup_1]

	//! [dma_rx_setup_2]
	dma_get_config_defaults(&rx_config);
	//! [dma_rx_setup_2]

	//! [dma_rx_setup_3]
	rx_config.peripheral_trigger = CONF_PERIPHERAL_TRIGGER_RX;
	rx_config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	//! [dma_rx_setup_3]

	//! [dma_rx_setup_4]
	dma_allocate(rx_resource, &rx_config);
	//! [dma_rx_setup_4]
}



void Axelerometr::setup_transfer_descriptor_tx()
{
	DmacDescriptor *tx_descriptor = &example_descriptor_tx;
	//! [dma_tx_setup_5]
	struct dma_descriptor_config tx_descriptor_config;
	//! [dma_tx_setup_5]

	//! [dma_tx_setup_6]
	dma_descriptor_get_config_defaults(&tx_descriptor_config);
	//! [dma_tx_setup_6]

	//! [dma_tx_setup_7]
	tx_descriptor_config.beat_size = DMA_BEAT_SIZE_BYTE;
	tx_descriptor_config.dst_increment_enable = false;
	tx_descriptor_config.block_transfer_count = sizeof(buffer_tx)/sizeof(uint8_t);
	tx_descriptor_config.source_address = (uint32_t)buffer_tx + sizeof(buffer_tx);
	tx_descriptor_config.destination_address = (uint32_t)(&spi_master_instance_ADXL.hw->SPI.DATA.reg);
	//! [dma_tx_setup_7]

	//! [dma_tx_setup_8]
	dma_descriptor_create(tx_descriptor, &tx_descriptor_config);
	//! [dma_tx_setup_8]
}

void Axelerometr::setup_transfer_descriptor_rx()
{
	DmacDescriptor *rx_descriptor = &example_descriptor_rx;
	//! [dma_rx_setup_5]
	struct dma_descriptor_config rx_descriptor_config;
	//! [dma_rx_setup_5]

	//! [dma_rx_setup_6]
	dma_descriptor_get_config_defaults(&rx_descriptor_config);
	//! [dma_rx_setup_6]

	//! [dma_rx_setup_7]
	rx_descriptor_config.beat_size = DMA_BEAT_SIZE_BYTE;
	rx_descriptor_config.src_increment_enable = false;
	rx_descriptor_config.block_transfer_count = sizeof(buffer_read.data)/sizeof(uint8_t);// sizeof(buffer_rx)/sizeof(uint8_t);
	rx_descriptor_config.source_address =(uint32_t)(&spi_master_instance_ADXL.hw->SPI.DATA.reg);
	rx_descriptor_config.destination_address =(uint32_t)buffer_read.data + sizeof(buffer_read.data);
	//! [dma_rx_setup_7]

	//! [dma_rx_setup_8]
	dma_descriptor_create(rx_descriptor, &rx_descriptor_config);
	//! [dma_rx_setup_8]
}

void Axelerometr::StartDMA()
{
	spi_select_slave(&spi_master_instance_ADXL, &slave_ADXL, true);
	dma_start_transfer_job(&example_resource_rx);
	dma_start_transfer_job(&example_resource_tx);
}

void Axelerometr::StartReadDMA()
{
	ReadData = false;
	StartDMA();
}

void Axelerometr::Start_transfer_DMA()
{
	dma_start_transfer_job(&example_resource_rx);
	dma_start_transfer_job(&example_resource_tx);
}

void Axelerometr::StopDMA()
{
	spi_select_slave(&spi_master_instance_ADXL, &slave_ADXL, false);
}

void Axelerometr::WaitReady(Vibro_acceleration& signal)
{
	os_wrapper& os = *os_wrapper::getInstance();
	TaskHandle_t current = os.threadGetCurrentTID();

	if (X().TID() == current)
	{
		x_handle = current;
	}
	else if (Y().TID() == current)
	{
		y_handle = current;
	}
	else if(Z().TID() == current)
	{
		z_handle = current;
	}
	ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
}

/*����� ��� ��������� ������� ��� X*/
Axis& Axelerometr::X()
{
	static Axis axs("Axis-X");
	
	return axs;
}

/*����� ��� ��������� ������� ��� Y*/
Axis& Axelerometr::Y()
{
	static Axis axs("Axis-Y");
	return axs;
}

/*����� ��� ��������� ������� ��� Z*/
Axis& Axelerometr::Z()
{
	static Axis axs("Axis-Z");
	return axs;
}