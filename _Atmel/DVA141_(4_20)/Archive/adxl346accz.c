#include "adxl346accz.h"
#include "main.h"
#include <asf.h>

void ADXL_SetRegisterValue(uint8_t regAddress, uint8_t regValue)
{
	
	uint8_t data[] = {0x00, 0x00};
	
	data[0] = regAddress;
	data[1] = regValue;
	//data[1] = ((regValue & 0xFF00) >> 8);
	//data[2] = ((regValue & 0x00FF) >> 0);
	
	SPI_Write_ADXL(data);
}

uint8_t ADXL_GetRegisterValue(uint8_t regAddress)
{
	uint8_t data[] = {0x00, 0x00};
	uint8_t receivedData = 0x00;
	
	
	data[0] = regAddress  | 0x80;
	
	SPI_Write_ADXL(data);
	
	delay_us(30);
	
	SPI_Read_ADXL(data);
			
	//receivedData += (data[1] << 8);
	//receivedData += (data[2] << 0);

	receivedData += data[1];

	return receivedData;
}

uint16_t ADXL_Init(void)
{
	uint16_t status = 1;
	
	port_pin_set_output_level(PIN_PA06, 1);

	//ADXL_SetRegisterValue(AD5421_REG_CTRL,
	//AD5421_CTRL_WATCHDOG_DISABLE |
	//AD5421_CTRL_MIN_CURRENT	|
	//AD5421_CTRL_ADC_SOURCE_TEMP	|
	//AD5421_CTRL_ADC_ENABLE
	//);
	
	//if(ADXL_GetRegisterValue(AD5421_REG_CTRL) == 0x1280)
	//{
		//status = 0x0;
	//}
	
	ADXL_SetRegisterValue(DATA_FORMAT, 0x00);
	
	
	
	status = ADXL_GetRegisterValue(DEVID);
	
	return (status);
}


