/* 
* AD5421.h
*
* Created: 20.06.2016 13:41:29
* Author: savchenkors
*/

#include <asf.h>

#ifndef __AD5421_H__
#define __AD5421_H__


/******************************************************************************/
/* AD5421                                                                    */
/******************************************************************************/
/* Registers */
#define AD5421_REG_DAC_DATA				0x1
#define AD5421_REG_CTRL					0x2
#define AD5421_REG_OFFSET				0x3
#define AD5421_REG_GAIN					0x4
/* load dac and fault shared the same register number. Writing to it will cause
 * a dac load command, reading from it will return the fault status register */
#define AD5421_REG_LOAD_DAC				0x5
#define AD5421_REG_FAULT				0x5
#define AD5421_REG_FORCE_ALARM_CURRENT	0x6
#define AD5421_REG_RESET				0x7
#define AD5421_REG_START_CONVERSION		0x8
#define AD5421_REG_NOOP					0x9

#define AD5421_CTRL_WATCHDOG_TIME(x)	(((x) & 0x7) << 13)
#define AD5421_CTRL_WATCHDOG_DISABLE	(1 << 12)
#define AD5421_CTRL_AUTO_FAULT_READBACK	(1 << 11)
#define AD5421_CTRL_MIN_CURRENT			(1 << 9)
#define AD5421_CTRL_ADC_SOURCE_TEMP		(1 << 8)
#define AD5421_CTRL_ADC_ENABLE			(1 << 7)
#define AD5421_CTRL_PWR_DOWN_INT_VREF	(1 << 6)

#define AD5421_FAULT_SPI				(1 << 15)
#define AD5421_FAULT_PEC				(1 << 14)
#define AD5421_FAULT_OVER_CURRENT		(1 << 13)
#define AD5421_FAULT_UNDER_CURRENT		(1 << 12)
#define AD5421_FAULT_TEMP_OVER_140		(1 << 11)
#define AD5421_FAULT_TEMP_OVER_100		(1 << 10)
#define AD5421_FAULT_UNDER_VOLTAGE_6V	(1 << 9)
#define AD5421_FAULT_UNDER_VOLTAGE_12V	(1 << 8)

#define AD5421_READ						(1 << 7)




class AD5421
{
//variables
public:
protected:
private:

//functions
public:

	static void AD5421_SetRegisterValue(uint8_t regAddress, uint16_t regValue);
	static uint16_t AD5421_GetRegisterValue(uint8_t regAddress);
	static uint16_t AD5421_Init(void);
	static uint16_t AD5421_GetTemperature(void);
	
	static void configure_spi_master_AD5421(void);
	static void SPI_Write_AD5421(uint8_t* data);
	static void SPI_Read_AD5421(uint8_t* data);

	AD5421();
	~AD5421();
protected:
	
private:
	AD5421( const AD5421 &c );
	AD5421& operator=( const AD5421 &c );

}; //AD5421

#endif //__AD5421_H__
