/*
* iSignal.h
*
* Created: 17.06.2016 14:38:27
*  Author: drachevam
*/


#ifndef ISIGNAL_H_
#define ISIGNAL_H_

#include "os_wrapper.h"
#include "arm_math.h"

#define sampleSize 64 //кол-во отсчетов в выборке
#define sampleScale 20 //диапазон для масштабирования в q31 и расчета коэф. преобр. в ЦАП

#define SIZE_VALUE_DECADE_MS (10)
#define SIZE_VALUE_HUNDER_MS (10)
#define SIGNAL_BUFFER_SIZE  (32)

typedef enum
{
	MAXIMUM_INDEX = 0,
	RMS_INDEX = 1,	
	MINIMUM_INDEX = 2,
	};

class iSignal
{
	volatile q31_t amplitude;
	volatile q31_t rms;
	volatile q31_t peakToPeak;
	q31_t buffer[SIGNAL_BUFFER_SIZE];
	protected:
	void Amplitude(q31_t value);
	void PeakToPeak(q31_t value);
	void RMS(q31_t value);
	q31_t decade_ms[3][SIZE_VALUE_DECADE_MS];   //буфер средние значения за 10 мс.	
	q31_t hunder_ms[3][SIZE_VALUE_HUNDER_MS];  //буфер среднее значение за 100 мс.
	uint8_t index_decade[3];
	uint8_t index_hunder[3];
	
	public:	
	iSignal();
	
	/*метод переводит значение value в значение int * 1000 
	например 0,301 в числе q31_t переведется в 301 */
	int32_t ConvertToInt(q31_t value);
	
	virtual	~iSignal();
	
	virtual q31_t Amplitude();
	
	virtual q31_t PeakToPeak();
	
	virtual q31_t RMS();
	
	virtual void Calculate(q31_t* data, size_t data_size);
};



#endif /* ISIGNAL_H_ */