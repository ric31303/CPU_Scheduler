#include "IO.h"

IO::IO(){
}

IO::IO(std::shared_ptr<std::list<std::shared_ptr<Thread>>> ioList){
    IOList = ioList;
}

IO::~IO()
{
}

std::shared_ptr<Thread> IO::run() {//run this every clock tick
    if (IOList->size() > 0){
        setWorkingThread(IOList->front());
        if (currThread->burstTime.back() > 0){
            currThread->burstTime.back()--;
            return NULL;
        }else {
            std::shared_ptr<Thread> oldThread = currThread;
            oldThread->burstTime.pop_back();
            oldThread->needsIO = false;
            return oldThread;
        }
    }
    return NULL;
}

bool IO::getStatus() {
    return IOList->size() > 0;
}

void IO::setWorkingThread(std::shared_ptr<Thread> thread) {
    currThread = thread;
}

std::shared_ptr<Thread> IO::getWorkingThread() {
    return currThread;
}
