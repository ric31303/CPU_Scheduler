#pragma once

class ScheduleStrategy {
public:
	//both of these are pure virtual
	virtual void run() = 0;
	virtual void schedule() = 0;
};