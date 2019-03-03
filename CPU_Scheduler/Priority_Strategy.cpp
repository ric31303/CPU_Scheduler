#include "Priority_Strategy.h"

Priority_Strategy::Priority_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    //nothing needed here for SJF
}

void Priority_Strategy::run() {
    //nothing needed here for SJF
}

void Priority_Strategy::schedule() {
    std::shared_ptr<Thread> threadToSchedule;
    for (std::list<std::shared_ptr<Thread>>::iterator it = context->ReadyList->begin(); it != context->ReadyList->end(); ++it){
        if (comparePriority(*it, threadToSchedule)){
            threadToSchedule = *it;
        }
    }
    context->ReadyList->remove(threadToSchedule);
    context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
    
}

void Priority_Strategy::addThread() {
    //nothing needed here for SJF
}

bool Priority_Strategy::comparePriority(std::shared_ptr<Thread> threadA, std::shared_ptr<Thread> threadB){
    return threadA->priority < threadB->priority;
}
