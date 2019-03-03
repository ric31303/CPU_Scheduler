#include "PreemptPriority_Strategy.h"

PreemptPriority_Strategy::PreemptPriority_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    //nothing needed here for SJF
}

void PreemptPriority_Strategy::run() {
    std::shared_ptr<Thread> threadToSchedule = std::make_shared<Thread>();
    for (auto& it: *context->ReadyList){
        if (it->priority < threadToSchedule->priority ){
            threadToSchedule = it;
        }
    }
    if (context->scheduler->getCurrThread() != NULL ){
        if (context->scheduler->getCurrThread()->priority < threadToSchedule->priority ){
            return; // current thread priority higher, no preempt
        }
    }
    context->ReadyList->remove(threadToSchedule);
    context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
}

void PreemptPriority_Strategy::schedule() {
    std::shared_ptr<Thread> threadToSchedule = std::make_shared<Thread>();
    if (context->ReadyList->size() > 0){
        for (auto& it: *context->ReadyList){
            if (it->priority < threadToSchedule->priority){
                threadToSchedule = it;
            }
        }
        context->ReadyList->remove(threadToSchedule);
        context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
        return ;
    }
    context->scheduler->preempt(NULL); //move scheduled thread to CPU and save the last thread
}

void PreemptPriority_Strategy::addThread() {
    //nothing needed here for SJF
}
