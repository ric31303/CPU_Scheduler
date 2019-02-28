#pragma once

#include <List>
#include <memory>

#include "Thread.h"

class Scheduler;

class Context {
public:

	std::shared_ptr<std::list<std::shared_ptr<Thread>>> FinishedList;
	std::shared_ptr<std::list<std::shared_ptr<Thread>>> ReadyList;
	std::shared_ptr<std::list<std::shared_ptr<Thread>>> BlockedList;

	std::shared_ptr<Scheduler> scheduler;
	
	Context(std::shared_ptr<std::list<std::shared_ptr<Thread>>> fl,
		std::shared_ptr<std::list<std::shared_ptr<Thread>>> rl,
		std::shared_ptr<std::list<std::shared_ptr<Thread>>> bl,
		std::shared_ptr<Scheduler> s) {

		FinishedList = fl;
		ReadyList = rl;
		BlockedList = bl;
		scheduler = s;
	}
};