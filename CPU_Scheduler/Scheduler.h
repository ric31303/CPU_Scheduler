#pragma once

#include <List>
#include <memory>

#include "CPU.h"

#include "ScheduleStrategy.h" //predefines Context
#include "Context.h"          //predefines Scheduler

class Scheduler
{
public:
	Scheduler();
	Scheduler(std::shared_ptr<CPU> c, std::shared_ptr<ScheduleStrategy> s);
	~Scheduler();

	void run();

	void addNewThread(std::shared_ptr<Thread> thread);
	void readyThread(std::shared_ptr<Thread> thread);//move a specific thread from Blocked List to Ready List
	void blockThread(std::shared_ptr<Thread> thread);//move a specific thread from Ready List to Blocked List
	std::shared_ptr<Thread> preempt(std::shared_ptr<Thread> thread);//preempt the current thread on the CPU
	void finishThread(std::shared_ptr<Thread> thread);//move a specific thread from Ready List to Finished List

private:
	std::shared_ptr<CPU> cpu;
	std::list<std::shared_ptr<Thread>> FinishedList;
	std::list<std::shared_ptr<Thread>> ReadyList;
	std::list<std::shared_ptr<Thread>> BlockedList;

	std::shared_ptr<ScheduleStrategy> strat;
};

