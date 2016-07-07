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
	q31_t max_min[2];
	q31_t max = 0;
	uint32_t index;
	arm_copy_q31(data, buffer, SIGNAL_BUFFER_SIZE);
	arm_max_q31(buffer, SIGNAL_BUFFER_SIZE, &max_min[0], &index);
	arm_min_q31(buffer, SIGNAL_BUFFER_SIZE, &max_min[1], &index);
	arm_abs_q31(max_min, max_min, 2);
	
	arm_max_q31(max_min, 2, &max, &index);	
	decade_ms[AMPLITUDE_INDEX][index_decade[AMPLITUDE_INDEX]++] = max;
	if (index_decade[AMPLITUDE_INDEX] >= SIZE_VALUE_DECADE_MS)
	{
		index_decade[AMPLITUDE_INDEX] = 0;
	}
	
	arm_max_q31(decade_ms[AMPLITUDE_INDEX] , SIZE_VALUE_DECADE_MS, &max, &index);	
	hunder_ms[AMPLITUDE_INDEX][index_hunder[AMPLITUDE_INDEX]++] = max;
	if (index_hunder[AMPLITUDE_INDEX] >= SIZE_VALUE_HUNDER_MS)
	{
		index_hunder[AMPLITUDE_INDEX] = 0;		
	}	
	arm_max_q31(hunder_ms[AMPLITUDE_INDEX] , SIZE_VALUE_HUNDER_MS, &max, &index);
	amplitude = max;
}