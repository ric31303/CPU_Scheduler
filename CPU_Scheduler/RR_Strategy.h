#pragma once
#include "Scheduler.h" //needs stuff from Scheduler and Scheduler contatins ScheduleStrategy

class RR_Strategy : public ScheduleStrategy {
public:
    
    RR_Strategy(std::shared_ptr<Context> c);
    void run();
    void schedule();
    void addThread();
    
private:
    const size_t timeQuantum = 3;
};
