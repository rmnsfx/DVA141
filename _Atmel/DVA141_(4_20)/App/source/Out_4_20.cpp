/*
* Out_4_20.cpp
*
* Created: 10.06.2016 9:54:54
*  Author: drachevam
*/

#include "Out_4_20.h"


Out_4_20::Out_4_20()
{
	if( xSemaphore == NULL)
	{
		xSemaphore = xSemaphoreCreateBinaryStatic(&Out_4_20::xSemaphoreBuffer);
		configASSERT( xSemaphore );
	}
	xSemaphoreTake( xSemaphore, portMAX_DELAY );
}

Out_4_20::~Out_4_20()
{
	xSemaphoreGive( xSemaphore );
}
