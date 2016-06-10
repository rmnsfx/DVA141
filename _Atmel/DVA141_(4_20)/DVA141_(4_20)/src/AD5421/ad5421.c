#include "ad5421.h"
#include "main.h"


void AD5421_SetRegisterValue(uint8_t regAddress, uint16_t regValue)
{
	//volatile unsigned char statuscode;
	uint8_t data[] = {0x00, 0x00, 0x00};
	
	data[0] = regAddress;
	data[1] = ((regValue & 0xFF00) >> 8);
	data[2] = ((regValue & 0x00FF) >> 0);
	
	SPI_Write_AD5421(data);
}

uint16_t AD5421_GetRegisterValue(uint8_t regAddress)
{
	uint8_t data[] = {0x00, 0x00, 0x00};
	uint16_t receivedData = 0x00;
	//volatile unsigned char statuscode;
	
	data[0] = regAddress | AD5421_READ;
	
	SPI_Write_AD5421(data);
	
	delay_us(30);
	
	SPI_Read_AD5421(data);
	
	receivedData += (data[1] << 8);
	receivedData += (data[2] << 0);

	return receivedData;
}

uint16_t AD5421_Init(void)
{
	uint16_t status = 1;
	
	port_pin_set_output_level(PIN_PA18, 1);

	AD5421_SetRegisterValue(AD5421_REG_CTRL,
	AD5421_CTRL_WATCHDOG_DISABLE |
	//AD5421_CTRL_MIN_CURRENT	|
	AD5421_CTRL_ADC_SOURCE_TEMP	|
	AD5421_CTRL_ADC_ENABLE
	);
	
	if(AD5421_GetRegisterValue(AD5421_REG_CTRL) == 0x1280)
	{
		status = 0x0;
	}
	
	return (status);
}

uint16_t AD5421_GetTemperature(void)
{
	uint16_t temp = 0;
	temp = (uint16_t) AD5421_GetRegisterValue(AD5421_REG_FAULT) & 0xFF;
	temp = temp - 128;
	temp = temp * 1.771;
	temp = 125 - temp;
	
	return temp;
	
}


