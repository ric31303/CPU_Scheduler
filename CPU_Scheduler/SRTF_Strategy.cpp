#include "SRTF_Strategy.h"

SRTF_Strategy::SRTF_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    //nothing needed here for FIFO
}

void SRTF_Strategy::run() {
    std::shared_ptr<Thread> threadToSchedule = std::make_shared<Thread>();
    for (auto& it: *context->ReadyList){
        if (compareBurstTime(it, threadToSchedule)){
            threadToSchedule = it;
        }
    }
    if (compareBurstTime(threadToSchedule, context->scheduler->getCurrThread()))
        context->ReadyList->remove(threadToSchedule);
        context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
}

void SRTF_Strategy::schedule() {
    std::shared_ptr<Thread> threadToSchedule = std::make_shared<Thread>();
    for (auto& it: *context->ReadyList){
        if (compareBurstTime(it, threadToSchedule)){
            threadToSchedule = it;
        }
    }
    context->ReadyList->remove(threadToSchedule);
    context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
}

void SRTF_Strategy::addThread() {
    //nothing needed here for FIFO
}

bool SRTF_Strategy::compareBurstTime(std::shared_ptr<Thread> threadA, std::shared_ptr<Thread> threadB){
    return threadA->prevBurstTime < threadB->prevBurstTime;
}
