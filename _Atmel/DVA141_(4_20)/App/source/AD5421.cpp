/* 
* AD5421.cpp
*
* Created: 20.06.2016 13:41:29
* Author: savchenkors
*/


#include "AD5421.h"

static struct spi_module spi_master_instance_AD5421;
static struct spi_slave_inst slave_AD5421;


void AD5421::configure_spi_master_AD5421(void)
{
	//! [config]
	struct spi_config config_spi_master;
	//! [config]
	//! [slave_config]
	struct spi_slave_inst_config slave_dev_config;
	//! [slave_config]
	/* Configure and initialize software device instance of peripheral slave */
	//! [slave_conf_defaults]
	spi_slave_inst_get_config_defaults(&slave_dev_config);
	//! [slave_conf_defaults]
	//! [ss_pin]
	slave_dev_config.ss_pin = PIN_PA18;
	slave_dev_config.address_enabled = false;
	//! [ss_pin]
	//! [slave_init]
	spi_attach_slave(&slave_AD5421, &slave_dev_config);
	//! [slave_init]
	/* Configure, initialize and enable SERCOM SPI module */
	//! [conf_defaults]
	spi_get_config_defaults(&config_spi_master);
	//! [conf_defaults]
	//! [mux_setting]
	config_spi_master.mux_setting = SPI_SIGNAL_MUX_SETTING_D;
	//! [mux_setting]
	
	/* Configure pad 0 for MOSI */
	//! [di]
	config_spi_master.pinmux_pad0 =  PINMUX_PA16D_SERCOM3_PAD0;
	//! [di]
	/* Configure pad 1 for CLOCK */
	//! [ss]
	config_spi_master.pinmux_pad1 = PINMUX_PA17D_SERCOM3_PAD1;
	//! [ss]
	/* Configure pad 2 for CS */
	//! [do]
	config_spi_master.pinmux_pad2 = PINMUX_UNUSED;
	//! [do]
	/* Configure pad 3 for MISO */
	//! [sck]
	config_spi_master.pinmux_pad3 = PINMUX_PA19D_SERCOM3_PAD3;
	//! [sck]
	
	
	config_spi_master.mode             = SPI_MODE_MASTER;
	config_spi_master.data_order       = SPI_DATA_ORDER_MSB;
	config_spi_master.transfer_mode    = SPI_TRANSFER_MODE_1;
	config_spi_master.character_size   = SPI_CHARACTER_SIZE_8BIT;
	config_spi_master.run_in_standby   = false;
	config_spi_master.receiver_enable  = true;
	config_spi_master.generator_source = GCLK_GENERATOR_1;
	config_spi_master.mode_specific.master.baudrate = 1000000;
	config_spi_master.master_slave_select_enable = true;
	config_spi_master.select_slave_low_detect_enable = false;
	
	//! [init]
	spi_init(&spi_master_instance_AD5421, SERCOM3, &config_spi_master);
	//! [init]

	//! [enable]
	spi_enable(&spi_master_instance_AD5421);
	//! [enable]

}

void AD5421::SPI_Write_AD5421(uint8_t* data)
{
	port_pin_set_output_level(PIN_PA18, 0);
	spi_write_buffer_wait(&spi_master_instance_AD5421, data, 3);
	port_pin_set_output_level(PIN_PA18, 1);
}

void AD5421::SPI_Read_AD5421(uint8_t* data)
{
	port_pin_set_output_level(PIN_PA18, 0);
	//spi_read_buffer_wait(&spi_master_instance_AD5421, data, 3, 0);
	spi_transceive_buffer_wait(&spi_master_instance_AD5421, data, data, 3);
	port_pin_set_output_level(PIN_PA18, 1);
}



void AD5421::AD5421_SetRegisterValue(uint8_t regAddress, uint16_t regValue)
{
	//volatile unsigned char statuscode;
	uint8_t data[] = {0x00, 0x00, 0x00};
	
	data[0] = regAddress;
	data[1] = ((regValue & 0xFF00) >> 8);
	data[2] = ((regValue & 0x00FF) >> 0);
	
	AD5421::SPI_Write_AD5421(data);
}

uint16_t AD5421::AD5421_GetRegisterValue(uint8_t regAddress)
{
	uint8_t data[] = {0x00, 0x00, 0x00};
	uint16_t receivedData = 0x00;
	//volatile unsigned char statuscode;
	
	data[0] = regAddress | AD5421_READ;
	
	AD5421::SPI_Write_AD5421(data);
	
	AD5421::SPI_Read_AD5421(data);
	
	receivedData += (data[1] << 8);
	receivedData += (data[2] << 0);

	return receivedData;
}

uint16_t AD5421::AD5421_Init(void)
{
	uint16_t status = -1;
	
	configure_spi_master_AD5421();
	
	port_pin_set_output_level(PIN_PA18, 1);

	AD5421_SetRegisterValue(AD5421_REG_RESET, 0);	
	
	for(int i=0; i<2500; i++){};
	
	AD5421_SetRegisterValue(AD5421_REG_OFFSET, 32768);
	
	AD5421_SetRegisterValue(AD5421_REG_GAIN, 65535);

	for(int i=0; i<2500; i++){};
		
	AD5421_SetRegisterValue(AD5421_REG_FORCE_ALARM_CURRENT, 0x1);
	
	AD5421_SetRegisterValue(AD5421_REG_START_CONVERSION, 0x1);

	AD5421_SetRegisterValue(AD5421_REG_CTRL,
	AD5421_CTRL_WATCHDOG_DISABLE |	 
	//AD5421_CTRL_MIN_CURRENT	|
	//AD5421_CTRL_ADC_SOURCE_TEMP	|	
	AD5421_CTRL_ADC_ENABLE
	);
	

	
	if(AD5421_GetRegisterValue(AD5421_REG_CTRL) == 0x1280)
	{
		status = 0x0;
	}
	
	return (status);
}

uint16_t AD5421::AD5421_GetTemperature(void)
{
	uint16_t temp = 0;
	temp = (uint16_t) AD5421_GetRegisterValue(AD5421_REG_FAULT) & 0xFF;
	temp = temp - 128;
	temp = temp * 1.771;
	temp = 125 - temp;
	
	return temp;
	
}

