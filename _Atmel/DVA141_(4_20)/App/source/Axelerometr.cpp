/*
* Axelerometr.cpp
*
* Created: 17.06.2016 15:03:23
*  Author: drachevam
*/
#include "Axelerometr.h"

/*метод для получения объекта оси X*/
Axis& Axelerometr::X()
{
	static Axis axs("Axis-X");
	
	return axs;
}

/*метод для получения объекта оси Y*/
Axis& Axelerometr::Y()
{
	static Axis axs("Axis-Y");
	return axs;
}

/*метод для получения объекта оси Z*/
Axis& Axelerometr::Z()
{
	static Axis axs("Axis-Z");
	return axs;
}