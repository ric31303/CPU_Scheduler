#include "CPU.h"

CPU::CPU()
{
}


CPU::~CPU()
{
}

//TODO: finish this
bool CPU::run() {//run this every clock tick
	currTime--; //TODO: change this to use a real time datatype at some point
	burstTimeLeft--;
	
}

bool CPU::getStatus() {//TODO: finish this
	if (burstTimeLeft <= 0) {//TODO: this will become more important if/when we actually use a proper time datatype
		return false;
	}
	else {
		return true;
	}
}

size_t CPU::getLengthOfCurrentBurst(){
	return currTime - currBurstStart;
}

Thread* CPU::setWorkingThread(Thread* newThread) {
	if (burstTimeLeft <= 0) {//TODO: this will become more important if/when we actually use a proper time datatype
		currThread->burstTime.pop_back();
	} else {
		currThread->burstTime.at(currThread->burstTime.max_size - 1) = burstTimeLeft;
	}
	
	Thread* oldThread = currThread;
	currThread = newThread;
	newThread->addBurstTime(currTime);
	burstTimeLeft = currThread->burstTime.back;
	currBurstStart = currTime;

	return oldThread;
}

Thread* CPU::getWorkingThread() {
	return currThread;
}