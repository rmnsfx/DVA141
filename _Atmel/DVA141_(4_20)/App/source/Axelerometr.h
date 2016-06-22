/*
* Axelerometr.h
*
* Created: 17.06.2016 14:58:12
*  Author: drachevam
*/


#ifndef AXELEROMETR_H_
#define AXELEROMETR_H_
#include "Axis.h"
#include "os_wrapper.h"

class Axelerometr:public Singleton<Axelerometr>
{
	public:
	Axis& X();
	Axis& Y();
	Axis& Z();
	protected:
	friend class Singleton<Axelerometr> ;
};


#endif /* AXELEROMETR_H_ */