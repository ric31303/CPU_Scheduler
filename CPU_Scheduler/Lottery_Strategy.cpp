#include "Lottery_Strategy.h"

Lottery_Strategy::Lottery_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
    randomOffset = (size_t)time(NULL);
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
            lotteryPool->push_back(it); //every job get one ticket
            if (it->prevBurstTime < timeQuantum){
                lotteryPool->push_back(it);  //shorter job get one more ticket
            }
        }
        std::list<std::shared_ptr<Thread>>::iterator it = lotteryPool->begin();
        std::advance(it, (rand()+randomOffset)% lotteryPool->size());  //random choose one frome the pool
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
