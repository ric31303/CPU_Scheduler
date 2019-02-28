#include "Scheduler.h" //needs stuff from Scheduler and Scheduler contatins ScheduleStrategy

class FIFO_Strategy : ScheduleStrategy {
public:

	FIFO_Strategy(std::shared_ptr<Context> c) : ScheduleStrategy(c) {
		//nothing needed here for FIFO
	}

	void run() {
		//nothing needed here for FIFO
	}

	void schedule() {
		std::shared_ptr<Thread> threadToSchedule = context->ReadyList->back();
		context->ReadyList->pop_back();
		std::shared_ptr<Thread> lastThread = context->scheduler->preempt(threadToSchedule); //move scheduled thread to CPU and save the last thread
		context->scheduler->finishThread(lastThread);
	}

	void addThread() {
		//nothing needed here for FIFO
	}
};