#include "Scheduler.h"


Scheduler::Scheduler(){//TODO: do this once we have strategies 
	
}

Scheduler::Scheduler(std::shared_ptr<CPU> c, std::shared_ptr<ScheduleStrategy> s){
	cpu = c;
	strat = s;
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

void Scheduler::addNewThread(std::shared_ptr<Thread> thread) {
	readyList->push_back(thread);
	strat->addThread(); //TODO: should the strategy be allowed to push the added thread?
}

void Scheduler::readyThread(std::shared_ptr<Thread> thread) { //move a specific thread from Blocked List to Ready List
	blockedList->remove(thread);//TODO: try this first
	readyList->push_back(thread);
}

void Scheduler::blockThread(std::shared_ptr<Thread> thread) { //move a specific thread from Ready List to Blocked List
	readyList->remove(thread);//TODO: try this first
	blockedList->push_back(thread);
}

std::shared_ptr<Thread> Scheduler::preempt(std::shared_ptr<Thread> thread) { //preempt the current thread on the CPU
	return cpu->setWorkingThread(thread);
}

void Scheduler::finishThread(std::shared_ptr<Thread> thread) { //move a specific thread from Ready List to Finished List
	readyList->remove(thread);//TODO: try this first
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
		context = std::make_shared<Context>(finishedList, readyList, blockedList, this);
	}

	return context;
}
