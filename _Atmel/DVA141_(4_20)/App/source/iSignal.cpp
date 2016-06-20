#include "iSignal.h"


 iSignal::iSignal(const char* const ThreadName /*= "iSignal"*/, osPriority_t priority /*= osThreadPriorityNormal*/, uint32_t stack /*= 0*/): ios_thread(ThreadName,priority,stack)
{

}

/*
 * iSignal.cpp
 *
 * Created: 17.06.2016 14:48:01
 *  Author: drachevam
 */ 

void iSignal::main(void)
{

}

 iSignal::~iSignal()
{

}
