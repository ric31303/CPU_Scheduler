#include "Priority_Strategy.h"

Priority_Strategy::Priority_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    //nothing needed here for Priority
}

void Priority_Strategy::run() {
    //nothing needed here for Priority
}

void Priority_Strategy::schedule() {
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

void Priority_Strategy::addThread() {
    //nothing needed here for Priority
}
