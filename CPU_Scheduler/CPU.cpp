#include "CPU.h"

CPU::CPU(){
}


CPU::~CPU()
{
}

bool CPU::run() {//run this every clock tick
    currTime++; //TODO: change this to use a real time datatype at some point／
    if (burstTimeLeft != 0) {
        burstTimeLeft--;
    }

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
//    printf("[cpu] setWorkingThread\n");
    
    std::shared_ptr<Thread> oldThread = currThread;
    if (oldThread != NULL) {
        
        if (burstTimeLeft > 0) {//TODO: this will become more important if/when we actually use a proper time datatype
            if (newThread == NULL){
                currBurstStart = currTime;
                return NULL;    // if no newThread and not completed don't preempt
            }
            oldThread->burstTime.back() = burstTimeLeft;
        } else {
            oldThread->burstTime.pop_back();
            if (oldThread->burstTime.size() == 0){ // if no more bursttime then finished
                oldThread->finish = true;
            }else {
                oldThread->needsIO = true;  // otherwise means block by IO
            }
        }
        oldThread->prevBurstTime = getLengthOfCurrentBurst(); //record current burst
    }
    if (newThread == NULL) {//Stop executing
        burstTimeLeft = 0;
        currThread = newThread;
    }else{
        currThread = newThread;
        currThread->addWaitTime(currTime);
        burstTimeLeft = currThread->burstTime.back();
        currBurstStart = currTime;
    }
    return oldThread;
    
}

std::shared_ptr<Thread> CPU::getWorkingThread() {
    return currThread;
}
