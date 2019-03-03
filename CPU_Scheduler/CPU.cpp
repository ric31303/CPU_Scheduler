#include "CPU.h"

CPU::CPU(){

}


CPU::~CPU()
{
}

bool CPU::run() {//run this every clock tick
	currTime++; //TODO: change this to use a real time datatype at some point
	burstTimeLeft--;

	return getStatus();
}

bool CPU::getStatus() {
	if (burstTimeLeft <= 0) {//TODO: this will become more important if/when we actually use a proper time datatype
        
		return false;
	}
	else {
		return true; // true means not complete
	}
}

size_t CPU::getLengthOfCurrentBurst(){
	return currTime - currBurstStart;
}

std::shared_ptr<Thread> CPU::setWorkingThread(std::shared_ptr<Thread> newThread) {
	if (currThread == NULL) {//if this is the first thread
		currThread = newThread;
		newThread->addWaitTime(currTime);
		burstTimeLeft = currThread->burstTime.back();
		currBurstStart = currTime;
		return NULL;
	}

	if (getStatus()) {//TODO: this will become more important if/when we actually use a proper time datatype
		currThread->burstTime.back() = burstTimeLeft;
	} else {
        currThread->burstTime.pop_back();
        if (currThread->burstTime.size() <= 1){ // if no more bursttime then finished
            currThread->finish = true;
        }
	}
    
    std::shared_ptr<Thread> oldThread = currThread;
    oldThread->prevBurstTime = getLengthOfCurrentBurst(); //record current burst
    currThread = newThread;
    
    if (newThread == NULL) {//Stop executing
        burstTimeLeft = 0;
        return oldThread;
    }
	
	newThread->addWaitTime(currTime);
	burstTimeLeft = currThread->burstTime.back();
	currBurstStart = currTime;

	return oldThread;
}

std::shared_ptr<Thread> CPU::getWorkingThread() {
	return currThread;
}
