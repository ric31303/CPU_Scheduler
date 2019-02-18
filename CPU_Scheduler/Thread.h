#pragma once
#include <vector>

class Thread
{
public:
	size_t waitingTime;
	size_t lastReadyTime;
	bool needsIO; //TODO: impliment IO

	Thread() {
		waitingTime = 0;
		lastReadyTime = 0;
		burstTime.push_back(1); //one time unit of burst
		needsIO = false;
	}

	Thread(size_t entryTime, std::vector<size_t> burstT ) {
		waitingTime = 0;
		lastReadyTime = entryTime;
		burstTime = burstT;
		needsIO = false;
	}

	~Thread() {

	}

	void addBurstTime(size_t currTime) {//TODO: recalculates wait time everytime it gets schedualed. potential problem if never gets schedualed. Will we still need wait time in such a case? 
		waitingTime += currTime - lastReadyTime;
		lastReadyTime = currTime;
	}

	//this is public so that CPU can see it but absolutly nothing else should ever look at it
	//back = top of burstTime stack
	std::vector<size_t> burstTime;//TODO: This should be a bit more complicated including the burst/io
};

