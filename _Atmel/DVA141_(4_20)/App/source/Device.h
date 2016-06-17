/*
* Device.h
*
* Created: 09.06.2016 16:13:37
*  Author: drachevam
*/
#include <asf.h>

#ifndef DEVICE_H_
#define DEVICE_H_



class Device
{	
	protected:
	static void DeviceTask(void *pvParameters);
	static void RunTimeStatsTask(void *pvParameters);
	
	public:
	static void Run(void);
	static TaskHandle_t xTask1, xTask2;
	

};



#endif /* DEVICE_H_ */