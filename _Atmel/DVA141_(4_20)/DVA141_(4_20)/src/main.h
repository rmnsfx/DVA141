/*
 * main.h
 *
 * Created: 07.04.2016 11:54:09
 *  Author: savchenkors
 */ 

#include <asf.h>

#ifndef MAIN_H_
#define MAIN_H_


void SPI_Write_AD5421(uint8_t* data);
void SPI_Read_AD5421(uint8_t* data);
void SPI_Write_ADXL(uint8_t* data);
void SPI_Read_ADXL(uint8_t* data);



#endif /* MAIN_H_ */