/*
 * adxl346accz.h
 *
 * Created: 07.04.2016 15:04:41
 *  Author: savchenkors
 */ 


#ifndef ADXL346ACCZ_H_
#define ADXL346ACCZ_H_

#include <asf.h>



#define DEVID 0x00                              //Device ID R
#define THRESH_TAP 0x1D                         //Tap threshold. R/W
#define OFSX 0x1E                               //X-axis offset. R/W
#define OFSY 0x1F                               //Y-axis offset. R/W
#define OFSZ 0x20                               //Z-axis offset. R/W
#define DUR 0x21                                //Tap duration. R/W
#define Latent 0x22                             //Tap latency. R/W
#define Window 0x23                             //Tap window. R/W
#define THRESH_ACT 0x24                         //Activity threshold. R/W
#define THRESH_INACT 0x25                       //Inactivity threshold. R/W
#define TIME_INACT 0x26                         //Inactivity time. R/W
#define ACT_INACT_CTL 0x27                      //Axis enable control for activity and inactivity detection. R/W
#define THRESH_FF 0x28                          //Free-fall threshold. R/W
#define TIME_FF 0x29                            //Free-fall time. R/W
#define TAP_AXES 0x2A                           //Axis control for tap/double tap. R/W
#define ACT_TAP_STATUS 0x2B                     //Source of tap/double tap. R
#define BW_RATE 0x2C                            //Data rate and power mode control. R/W
#define POWER_CTL 0x2D                          //Power-saving features control. R/W
#define INT_ENABLE 0x2E                         //Interrupt enable control. R/W
#define INT_MAP 0x2F                            //Interrupt mapping control. R/W
#define INT_SOURCE 0x30                         //Source of interrupts. R
#define DATA_FORMAT 0x31                        //Data format control. R/W
#define DATAX0 0x32                             //X-Axis Data 0. R
#define DATAX1 0x33                             //X-Axis Data 1. R
#define DATAY0 0x34                             //Y-Axis Data 0. R
#define DATAY1 0x35                             //Y-Axis Data 1. R
#define DATAZ0 0x36                             //Z-Axis Data 0. R
#define DATAZ1 0x37                             //Z-Axis Data 1. R
#define FIFO_CTL 0x38                           //FIFO control. R/W
#define FIFO_STATUS 0x39                        //FIFO status. R


uint16_t ADXL_Init(void);
void ADXL_SetRegisterValue(uint8_t regAddress, uint8_t regValue);
uint8_t ADXL_GetRegisterValue(uint8_t regAddress);



#endif /* ADXL346ACCZ_H_ */