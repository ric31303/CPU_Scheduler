#pragma once

#include <list>
#include <memory>

#include "CPU.h"
#include "IO.h"
#include "ScheduleStrategy.h" //predefines Context
#include "Context.h"          //predefines Scheduler


class Scheduler : public std::enable_shared_from_this<Scheduler>
{
public:
	Scheduler();
	Scheduler(std::shared_ptr<CPU> c, std::shared_ptr<IO> &i, std::shared_ptr<ScheduleStrategy> s);
	~Scheduler();

	void run();

	void addNewThread(std::shared_ptr<Thread> thread);
	void readyThread(std::shared_ptr<Thread> thread);//move a specific thread from Blocked List to Ready List
	void blockThread(std::shared_ptr<Thread> thread);//move a specific thread from CPU to Blocked List
	std::shared_ptr<Thread> preempt(std::shared_ptr<Thread> thread);//preempt the current thread on the CPU
	void finishThread(std::shared_ptr<Thread> thread);//move a specific thread from CPU to Finished List
    void updateStrat(std::shared_ptr<ScheduleStrategy> _strat);//move a specific thread from Ready List to Finished List
	bool isFinished();
	size_t numFinished();
	std::shared_ptr<Context> getContext();
    std::shared_ptr<Thread> getCurrThread();
    size_t getCurrBurst();
    
    int* getTemp() {
        return temp;
    }
private:
	std::shared_ptr<CPU> cpu;
    std::shared_ptr<IO> io;
	std::shared_ptr<std::list<std::shared_ptr<Thread>>> finishedList;
    std::shared_ptr<std::list<std::shared_ptr<Thread>>> readyList;
	std::shared_ptr<std::list<std::shared_ptr<Thread>>> blockedList;
    
	std::shared_ptr<Context> context;
	std::shared_ptr<ScheduleStrategy> strat;
    
    int temp[4] = {-1, -1, -1 ,-1};
//    int tempMoveToCPU = -1;
//    int tempMoveToBlock = -1;
//    int tempMoveToFinished = -1;
//    int tempCPUTime = -1;
};

