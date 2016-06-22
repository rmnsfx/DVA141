#pragma once

#include "SystemsHeaders.h"


enum osPriority_t
{
	osThreadPriorityIdle = 0,          ///< priority: idle (lowest)
	osThreadPriorityLow ,          ///< priority: low
	osThreadPriorityBelowNormal ,          ///< priority: below normal
	osThreadPriorityNormal ,          ///< priority: normal (default)
	osThreadPriorityAboveNormal ,          ///< priority: above normal
	osThreadPriorityHigh ,          ///< priority: high
	osThreadPriorityRealtime ,          ///< priority: realtime (highest)
	osThreadPriorityError = 0x84 ///< system cannot determine priority or thread has illegal priority
};


class ios_thread
{
private:
	os_tid_t tid;
	const char* const name;
	const size_t stackSize;
	const osPriority_t priority;
protected:
	virtual void main(void) = 0;
	ios_thread(const char* const ThreadName = "Thread", osPriority_t priority =
		osThreadPriorityNormal, uint32_t stack = 0) :
		name(ThreadName), stackSize(stack + SYSTEMS_MINIMAL_STACK_SIZE), priority(
		priority)
	{
		this->tid = NO_TRHEAD_ID;
	}
public:
	virtual ~ios_thread()
	{
		//		os_wrapper* os = os_wrapper::getInstance();
		//		os->threadTerminate(this);
	}
	os_tid_t TID() const
	{
		return tid;
	}
	const char* Name()
	{
		return name;
	}

	size_t StackSize() const
	{
		return stackSize;
	}

	osPriority_t getPriority()
	{
		return priority;
	}
protected:
	//	friend class ios_wrapper;
	friend class os_wrapper;
};







