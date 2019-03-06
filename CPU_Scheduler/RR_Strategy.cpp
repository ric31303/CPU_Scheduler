#include "RR_Strategy.h"

RR_Strategy::RR_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    //nothing needed here for RR

}

void RR_Strategy::run() {
    if (context->scheduler->getCurrThread() != NULL ){
        if (context->scheduler->getCurrBurst() <= timeQuantum){ //check fortime quantum exceed
            return ;
        }
    }
    schedule();
}

void RR_Strategy::schedule() {
    
    if (context->ReadyList->size() > 0 ){
        std::shared_ptr<Thread> threadToSchedule = context->ReadyList->front();
        context->ReadyList->pop_front();
        context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
        return ;
    }
    context->scheduler->preempt(NULL);
}

void RR_Strategy::addThread() {
    //nothing needed here for RR
}
