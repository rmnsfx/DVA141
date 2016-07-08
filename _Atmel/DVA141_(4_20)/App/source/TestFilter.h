/*
 * TestFilter.h
 *
 * Created: 05.07.2016 10:53:05
 *  Author: drachevam
 */ 


#ifndef TESTFILTER_H_
#define TESTFILTER_H_

#include "os_wrapper.h"

class TestFilter: public ios_thread
{	
	public:
	TestFilter();
	virtual ~TestFilter();
	void main(void);
	};

#endif /* TESTFILTER_H_ */