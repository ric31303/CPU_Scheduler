#include "Scheduler.h"


Scheduler::Scheduler(){//TODO: do this once we have strategies
    readyList =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
    finishedList =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
    blockedList =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
}

Scheduler::Scheduler(std::shared_ptr<CPU> c, std::shared_ptr<IO> &i, std::shared_ptr<ScheduleStrategy> s){
	cpu = c;
	strat = s;
    readyList =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
    finishedList =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
    blockedList =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
    io = std::make_shared<IO>(blockedList);
    i = io;
}


Scheduler::~Scheduler(){
	//TODO: do wee need to do this?
}

void Scheduler::run() {
    
    // init temp
    temp[0]  = static_cast<int>(cpu->getClockTime());
    temp[1] = -1;
    temp[2] = -1;
    temp[3] = -1;
    
    printf("\n[Scheduler]cpu time: %zu\n",cpu->getClockTime());
    std::shared_ptr<Thread> wakeThread = io->run();  //run io
    if (wakeThread != NULL){
        readyThread(wakeThread);
    }
	if (!cpu->getStatus()) { //run cpu; if thread has completed:
		strat->schedule();
        cpu->run();
		return;
	}
	//otherwise run the strategy to see if we preempt
	strat->run();
    cpu->run();
    
}

void Scheduler::updateStrat(std::shared_ptr<ScheduleStrategy> _strat) {
    strat = _strat;
}

void Scheduler::addNewThread(std::shared_ptr<Thread> thread) {
    printf("/n[Scheduler] add new thread Id:%d\n",thread->id);
    readyList->push_back(thread);
    strat->addThread(); //TODO: should the strategy be allowed to push the added thread?
    tempReadyList->push_back(thread->id);

}

void Scheduler::readyThread(std::shared_ptr<Thread> thread) { //move a specific thread from Blocked List to Ready List
    printf("[Scheduler] wake thread Id:%d\n",thread->id);
    thread->lastReadyTime = cpu->getClockTime();
    blockedList->remove(thread);//TODO: try this first
	readyList->push_back(thread);
    tempReadyList->push_back(thread->id);
}

void Scheduler::blockThread(std::shared_ptr<Thread> thread) { //move a specific thread from CPU to Blocked List
    // set logging temp
    printf("[Scheduler] block thread Id:%d\n",thread->id);
    temp[2] = thread->id;
	blockedList->push_back(thread);
}

std::shared_ptr<Thread> Scheduler::preempt(std::shared_ptr<Thread> thread) { //preempt the current thread on the CPU
    
    // set logging temp
    if (thread != NULL) {
        temp[1] = thread->id;
    }
    std::shared_ptr<Thread> lastThread = cpu->setWorkingThread(thread);
    if( lastThread == NULL ){
        return lastThread;
    }
    
    
    if (lastThread->isFinished()){
        finishThread(lastThread);
    } else if (lastThread->needsIO){
        blockThread(lastThread);
    } else {
        printf("[Scheduler] go to ready %d", lastThread->id);
        lastThread->lastReadyTime = cpu->getClockTime();
        readyList->push_back(lastThread); // if not finished then push in to readyList
        tempReadyList->push_back(lastThread->id);
    }
    return lastThread;
}

void Scheduler::finishThread(std::shared_ptr<Thread> thread) { //move a specific thread from Ready List to Finished List
    thread->finishTime = cpu->getClockTime();

//    printf("[Scheduler] finish thread Id:%d, finishTime:%d \n",thread->id, thread->finishTime);
    // set logging temp
    temp[3] = thread->id;
	finishedList->push_back(thread);
}

bool Scheduler::isFinished(){
	return readyList->size() == 0 && blockedList->size() == 0  && getCurrThread() == NULL;
}

size_t Scheduler::numFinished(){
	return finishedList->size();
}

std::shared_ptr<Context> Scheduler::getContext() {
	if (context == NULL) {
		context = std::make_shared<Context>(finishedList, readyList, blockedList, shared_from_this());
	}

	return context;
}

std::shared_ptr<Thread> Scheduler::getCurrThread(){
    return cpu->getWorkingThread();
}

size_t Scheduler::getCurrBurst(){
    return cpu->getLengthOfCurrentBurst();
}

//size_t Scheduler::getAvgWaitingTime(){
//}
//
//size_t Scheduler::getAvgTATTime(){
//}
