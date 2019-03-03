#pragma once
#include "Scheduler.h" //needs stuff from Scheduler and Scheduler contatins ScheduleStrategy

class SRTF_Strategy : public ScheduleStrategy {
public:
    
    SRTF_Strategy(std::shared_ptr<Context> c);
    void run();
    void schedule();
    void addThread();
    
};
