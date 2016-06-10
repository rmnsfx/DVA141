/*
* Out_4_20.h
*
* Created: 09.06.2016 14:46:09
*  Author: drachevam
*/


#ifndef OUT_4_20_H_
#define OUT_4_20_H_

#include <asf.h>

class Out_4_20
{
	static SemaphoreHandle_t xSemaphore; //доступ к ресурсу
	static StaticSemaphore_t xSemaphoreBuffer;
	public:
	/*@param value значение тока в мј * 1000. (22,256 мј: value = 22256)*/
	void Current(uint32_t value);
	
	Out_4_20();
	virtual ~Out_4_20();
		
};



#endif /* OUT_4_20_H_ */