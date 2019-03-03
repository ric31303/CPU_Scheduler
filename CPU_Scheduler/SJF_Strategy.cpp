#include "SJF_Strategy.h"

SJF_Strategy::SJF_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    //nothing needed here for SJF
}

void SJF_Strategy::run() {
    //nothing needed here for SJF
}

void SJF_Strategy::schedule() {
    std::shared_ptr<Thread> threadToSchedule = std::make_shared<Thread>();
    for (auto& it: *context->ReadyList){
        if (it->prevBurstTime < threadToSchedule->prevBurstTime){
            threadToSchedule = it;
        }
    }
    context->ReadyList->remove(threadToSchedule);
    context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
    
}

void SJF_Strategy::addThread() {
    //nothing needed here for SJF
}
