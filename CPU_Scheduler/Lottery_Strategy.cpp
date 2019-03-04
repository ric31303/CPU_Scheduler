#include "Lottery_Strategy.h"

Lottery_Strategy::Lottery_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    
}

void Lottery_Strategy::run() {
    if (context->scheduler->getCurrThread() != NULL ){
        if (context->scheduler->getCurrBurst() <= timeQuantum){ //check fortime quantum exceed
            return ;
        }
    }
    schedule();
}

void Lottery_Strategy::schedule() {
    
    if (context->ReadyList->size() > 0){
        auto lotteryPool =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
        for (auto& it: *context->ReadyList){
            lotteryPool->push_back(it);
            if (it->prevBurstTime < timeQuantum){
                lotteryPool->push_back(it);
            }
        }
        std::list<std::shared_ptr<Thread>>::iterator it = lotteryPool->begin();
        std::advance(it, rand()% lotteryPool->size());
        std::shared_ptr<Thread> threadToSchedule = *it;
        context->ReadyList->remove(threadToSchedule);
        context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
        return ;
    }
    context->scheduler->preempt(NULL); //move scheduled thread to CPU and save the last thread
}

void Lottery_Strategy::addThread() {
    //nothing needed here for FIFO
}
