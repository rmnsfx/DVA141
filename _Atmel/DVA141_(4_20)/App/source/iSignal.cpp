/*
* iSignal.cpp
*
* Created: 17.06.2016 14:48:01
*  Author: drachevam
*/

#include "iSignal.h"


iSignal::iSignal()
{

}

iSignal::~iSignal()
{

}

q31_t iSignal::Amplitude()
{
	return amplitude;
}

q31_t iSignal::PeakToPeak()
{
	return peakToPeak;
}

q31_t iSignal::RMS()
{
	return rms;
}
