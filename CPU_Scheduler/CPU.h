#pragma once
#include "Thread.h"

class CPU
{
public:
	CPU();
	~CPU();

	bool run();//run this every clock tick
	bool getStatus();
	size_t getLengthOfCurrentBurst();
	Thread* setWorkingThread(Thread* newThread);
	Thread* getWorkingThread();

private:
	Thread* currThread;
	size_t burstTimeLeft;

	size_t currTime;
	size_t currBurstStart;

};

