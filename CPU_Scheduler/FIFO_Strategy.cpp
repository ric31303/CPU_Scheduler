#include "FIFO_Strategy.h"

FIFO_Strategy::FIFO_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    //nothing needed here for FIFO
}

void FIFO_Strategy::run() {
    //nothing needed here for FIFO
}

void FIFO_Strategy::schedule() {
    if (context->ReadyList->size() > 0 ){
        std::shared_ptr<Thread> threadToSchedule = context->ReadyList->front();
        context->ReadyList->pop_front();
        context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
        return ;
    }
    context->scheduler->preempt(NULL);
}

void FIFO_Strategy::addThread() {
    //nothing needed here for FIFO
}
