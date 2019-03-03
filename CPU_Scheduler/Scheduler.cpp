#include "Scheduler.h"


Scheduler::Scheduler(){//TODO: do this once we have strategies
   
}

Scheduler::Scheduler(std::shared_ptr<CPU> c, std::shared_ptr<ScheduleStrategy> s){
	cpu = c;
	strat = s;
    readyList =  std::make_shared<std::list<std::shared_ptr<Thread>>>();
}


Scheduler::~Scheduler(){
	//TODO: do wee need to do this?
}

void Scheduler::run() {
	if (!cpu->run()) { //run cpu; if thread has completed: 
		strat->schedule();
		return;
	}

	//otherwise run the strategy to see if we preempt
	strat->run();
}

void Scheduler::updateStrat(std::shared_ptr<ScheduleStrategy> _strat) {
    strat = _strat;
}

void Scheduler::addNewThread(std::shared_ptr<Thread> thread) {
    
    readyList->push_back(thread);
    strat->addThread(); //TODO: should the strategy be allowed to push the added thread?
}

void Scheduler::readyThread(std::shared_ptr<Thread> thread) { //move a specific thread from Blocked List to Ready List
	blockedList->remove(thread);//TODO: try this first
	readyList->push_back(thread);
}

void Scheduler::blockThread(std::shared_ptr<Thread> thread) { //move a specific thread from CPU to Blocked List
	blockedList->push_back(thread);
}

std::shared_ptr<Thread> Scheduler::preempt(std::shared_ptr<Thread> thread) { //preempt the current thread on the CPU
	std::shared_ptr<Thread> lastThread = cpu->setWorkingThread(thread);
    if ( lastThread->isFinished()){
       finishThread(lastThread);
    } else {
        readyList->push_back(lastThread); // if not finished then push in to readyList
    }
    return lastThread;
}

void Scheduler::finishThread(std::shared_ptr<Thread> thread) { //move a specific thread from CPU to Finished List
	finishedList->push_back(thread);
}

bool Scheduler::isFinished(){
	return readyList->size() == 0 && blockedList->size() == 0;
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

std::shared_ptr<Thread> Scheduler::getWorkingThread(){
    return cpu->getWorkingThread();
}
