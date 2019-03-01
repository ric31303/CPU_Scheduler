#pragma once

#include <List>
#include <memory>
#include "Thread.h"

class Context;

class ScheduleStrategy {
public:

	//both of these are pure virtual
	virtual void run() = 0; //Runs every clock cycle

	//This always runs when threads finish excecuting. if you need to preempt you will need to do that in run()
	virtual void schedule() = 0; //runs whenever a thread voluntarily leaves the CPU (etheir because it is finished or going to IO)
	virtual void addThread() = 0; //runs whenever a thread is added to the ready queue. This is primarily for sorting the readyList. //TODO: should this recieve the thread that was added?
protected:

	std::shared_ptr<Context> context;

	ScheduleStrategy(std::shared_ptr<Context> c) {
		context = c;
	}
};