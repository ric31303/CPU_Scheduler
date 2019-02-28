#pragma once

#include <List>
#include <memory>
#include "Thread.h"

class Context;

class ScheduleStrategy {
public:

	//both of these are pure virtual
	virtual void run() = 0;

	//This always runs when threads finish excecuting. if you need to preempt you will need to do that in run()
	virtual void schedule() = 0; 
	virtual void addThread() = 0;
protected:

	std::shared_ptr<Context> context;

	ScheduleStrategy(std::shared_ptr<Context> c) {
		context = c;
	}
};