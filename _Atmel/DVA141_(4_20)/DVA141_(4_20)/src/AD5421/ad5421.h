/*
 * ad5421.h
 *
 * Created: 07.04.2016 11:43:53
 *  Author: savchenkors
 */ 


#include <asf.h>

#ifndef AD5421_H_
#define AD5421_H_

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


void AD5421_SetRegisterValue(uint8_t regAddress, uint16_t regValue);
uint16_t AD5421_GetRegisterValue(uint8_t regAddress);
uint16_t AD5421_Init(void);
uint16_t AD5421_GetTemperature(void);


#endif /* AD5421_H_ */