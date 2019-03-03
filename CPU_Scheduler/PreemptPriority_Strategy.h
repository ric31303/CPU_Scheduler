#pragma once
#include "Scheduler.h" //needs stuff from Scheduler and Scheduler contatins ScheduleStrategy

class PreemptPriority_Strategy : public ScheduleStrategy {
public:
    
    PreemptPriority_Strategy(std::shared_ptr<Context> c);
    void run();
    void schedule();
    void addThread();
    
};
