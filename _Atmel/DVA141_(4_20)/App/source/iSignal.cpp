/*
* iSignal.cpp
*
* Created: 17.06.2016 14:48:01
*  Author: drachevam
*/

#include "iSignal.h"

iSignal::iSignal()
{
	memset( decade_ms, 0, sizeof(decade_ms));
	memset( index_decade, 0, sizeof(index_decade));
	memset( index_hunder, 0, sizeof(index_hunder));
	memset( hunder_ms, 0, sizeof(hunder_ms));
	memset( buffer, 0, sizeof(buffer));
	amplitude = 0;
	rms = 0;
	peakToPeak = 0;
}

int32_t iSignal::ConvertToInt(q31_t value)
{
	int32_t ret = 0;
	ret = (value * 64) / 1000 ;
}

iSignal::~iSignal()
{

}

q31_t iSignal::Amplitude()
{
	return amplitude;
}

void iSignal::Amplitude(q31_t value)
{
	amplitude = value;
}

q31_t iSignal::PeakToPeak()
{
	return peakToPeak;
}

void iSignal::PeakToPeak(q31_t value)
{
	peakToPeak = value;
}

q31_t iSignal::RMS()
{
	return rms;
}

void iSignal::RMS(q31_t value)
{
	rms = value;
}

void iSignal::Calculate(q31_t* data, size_t data_size)
{
	q31_t temp_value = 0;
	uint32_t index;
	
	arm_copy_q31(data, buffer, SIGNAL_BUFFER_SIZE);
	
	/*сохраняем MAXIMUM*/
	arm_max_q31(buffer, SIGNAL_BUFFER_SIZE, &temp_value, &index);
	decade_ms[MAXIMUM_INDEX][index_decade[MAXIMUM_INDEX]++] = temp_value;
	if (index_decade[MAXIMUM_INDEX] >= SIZE_VALUE_DECADE_MS)
	{
		index_decade[MAXIMUM_INDEX] = 0;
	}
	arm_max_q31(decade_ms[MAXIMUM_INDEX] , SIZE_VALUE_DECADE_MS, &temp_value, &index);
	hunder_ms[MAXIMUM_INDEX][index_hunder[MAXIMUM_INDEX]++] = temp_value;
	if (index_hunder[MAXIMUM_INDEX] >= SIZE_VALUE_HUNDER_MS)
	{
		index_hunder[MAXIMUM_INDEX] = 0;
	}
	
	/*сохраняем MINIMUM*/
	arm_min_q31(buffer, SIGNAL_BUFFER_SIZE, &temp_value, &index);
	decade_ms[MINIMUM_INDEX][index_decade[MINIMUM_INDEX]++] = temp_value;
	if (index_decade[MINIMUM_INDEX] >= SIZE_VALUE_DECADE_MS)
	{
		index_decade[MINIMUM_INDEX] = 0;
	}
	arm_max_q31(decade_ms[MINIMUM_INDEX] , SIZE_VALUE_DECADE_MS, &temp_value, &index);
	hunder_ms[MINIMUM_INDEX][index_hunder[MINIMUM_INDEX]++] = temp_value;
	if (index_hunder[MINIMUM_INDEX] >= SIZE_VALUE_HUNDER_MS)
	{
		index_hunder[MINIMUM_INDEX] = 0;
	}
	
	/*определение размаха и амплитуды*/
	{
		q31_t temp_minimum = 0;
		arm_max_q31(hunder_ms[MAXIMUM_INDEX] , SIZE_VALUE_HUNDER_MS, &temp_value, &index);
		arm_min_q31(hunder_ms[MINIMUM_INDEX] , SIZE_VALUE_HUNDER_MS, &temp_minimum, &index);	
		/*размах*/
		peakToPeak = temp_value - temp_minimum;
		/*амплитуда*/		
		arm_abs_q31(&temp_value, &temp_value, 1);
		arm_abs_q31(&temp_minimum, &temp_value, 1);
		amplitude = temp_value > temp_minimum ? temp_value : temp_minimum;
	}
		
	/*расчет СКЗ*/
	arm_rms_q31(buffer, SIGNAL_BUFFER_SIZE, &temp_value);
	decade_ms[RMS_INDEX][index_decade[RMS_INDEX]++] = temp_value;
	if (index_decade[RMS_INDEX] >= SIZE_VALUE_DECADE_MS)
	{
		index_decade[RMS_INDEX] = 0;
	}
	arm_rms_q31(decade_ms[RMS_INDEX], SIZE_VALUE_DECADE_MS, &temp_value);
	hunder_ms[RMS_INDEX][index_hunder[RMS_INDEX]++] = temp_value;
	if (index_hunder[RMS_INDEX] >= SIZE_VALUE_HUNDER_MS)
	{
		index_hunder[RMS_INDEX] = 0;
	}
	arm_rms_q31(hunder_ms[RMS_INDEX], SIZE_VALUE_HUNDER_MS, &temp_value);
	rms = temp_value;	
}