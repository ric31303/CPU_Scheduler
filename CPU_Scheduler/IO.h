#pragma once
#include <memory>

#include "Thread.h"

class IO
{
public:
    IO();
    ~IO();
    
    bool run();//run this every clock tick
    bool getStatus();
    size_t getLengthOfCurrentBurst();
    std::shared_ptr<Thread> setWorkingThread(std::shared_ptr<Thread> newThread);
    std::shared_ptr<Thread> getWorkingThread();
    
    size_t getClockTime() { return currTime; }
    
private:
    std::shared_ptr<Thread> currThread = NULL;
    size_t burstTimeLeft = 0;
    
    size_t currTime = 0;
    size_t currBurstStart = 0;
};

