#include "IO.h"

IO::IO(){
}


IO::~IO()
{
}

bool IO::run() {//run this every clock tick
    currTime++; //TODO: change this to use a real time datatype at some point／
    if (burstTimeLeft != 0) {
        burstTimeLeft--;
    }
    
    return getStatus();
}

bool IO::getStatus() {
    if (burstTimeLeft <= 0) {//TODO: this will become more important if/when we actually use a proper time datatype
        
        return false;
    }
    else {
        return true; // true means not complete
    }
}

size_t IO::getLengthOfCurrentBurst(){
    return currTime - currBurstStart;
}

std::shared_ptr<Thread> IO::setWorkingThread(std::shared_ptr<Thread> newThread) {
    printf("[cpu] setWorkingThread\n");
    
    std::shared_ptr<Thread> oldThread = currThread;
    if (oldThread != NULL) {
        oldThread->prevBurstTime = getLengthOfCurrentBurst(); //record current burst
        if (getStatus()) {//TODO: this will become more important if/when we actually use a proper time datatype
            oldThread->burstTime.back() = burstTimeLeft;
        } else {
            oldThread->burstTime.pop_back();
            if (oldThread->burstTime.size() <= 1){ // if no more bursttime then finished
                oldThread->finish = true;
            }else {
                oldThread->needsIO = true;  // otherwise means block by IO
            }
        }
    }
    if (newThread == NULL) {//Stop executing
        burstTimeLeft = 0;
    }else{
        currThread = newThread;
        currThread->addWaitTime(currTime);
        burstTimeLeft = currThread->burstTime.back();
        currBurstStart = currTime;
    }
    return oldThread;
    
}

std::shared_ptr<Thread> IO::getWorkingThread() {
    return currThread;
}
