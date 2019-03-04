#include "Lottery_Strategy.h"

Lottery_Strategy::Lottery_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    
    lotteryPool = std::make_shared<std::list<std::shared_ptr<Thread>>>();
}

void Lottery_Strategy::run() {
    if (context->scheduler->getCurrThread() != NULL ){
        if (context->scheduler->getCurrBurst() <= timeQuantum){ //check fortime quantum exceed
            return ;
        }
    }
    
    std::shared_ptr<Thread> threadToSchedule = context->ReadyList->front();
    if (threadToSchedule != NULL){
        context->ReadyList->pop_front();
    }
    context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
}

void Lottery_Strategy::schedule() {
    std::shared_ptr<Thread> threadToSchedule = context->ReadyList->front();
    if (threadToSchedule != NULL){
        context->ReadyList->pop_front();
    }
    context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
    
}

void Lottery_Strategy::addThread() {
    //nothing needed here for FIFO
}
