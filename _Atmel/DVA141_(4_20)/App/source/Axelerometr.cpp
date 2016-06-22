/*
* Axelerometr.cpp
*
* Created: 17.06.2016 15:03:23
*  Author: drachevam
*/
#include "Axelerometr.h"

/*����� ��� ��������� ������� ��� X*/
Axis& Axelerometr::X()
{
	static Axis axs("Axis-X");
	
	return axs;
}

/*����� ��� ��������� ������� ��� Y*/
Axis& Axelerometr::Y()
{
	static Axis axs("Axis-Y");
	return axs;
}

/*����� ��� ��������� ������� ��� Z*/
Axis& Axelerometr::Z()
{
	static Axis axs("Axis-Z");
	return axs;
}