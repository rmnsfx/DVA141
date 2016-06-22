#pragma once
#include "SystemsHeaders.h"
#include "ios_thread.h"
#include "Singleton.h"

using namespace std;

class os_wrapper: public Singleton<os_wrapper>
{
	private:
	static void Run(void* argument);
	public:
	os_wrapper(){};
	~os_wrapper(){};
	void kernelStart(void);
	bool threadCreate(ios_thread *piOsThread);
	//bool threadCreate(ios_thread &piOsThread);
	void threadTerminate(ios_thread *piOsThread);
	void delay(const uint32_t timeIncrement) const;
	os_tid_t threadGetCurrentTID();
	
	//protected:
	//friend class Singleton<os_wrapper> ;
};


