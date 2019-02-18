#pragma once
#include <vector>

class Thread
{
public:
	size_t waitingTime;
	size_t lastEntryTime;

	Thread() {
		waitingTime = 0;
		lastEntryTime = 0;
		burstTime.push_back(1); //one time unit of burst
	}

	Thread(size_t entryTime, std::vector<size_t> burstT ) {
		waitingTime = 0;
		lastEntryTime = entryTime;
		burstTime = burstT;
	}

	~Thread() {

	}

	void addBurstTime(size_t currTime) {
		waitingTime += currTime - lastEntryTime;
		lastEntryTime = currTime;
	}

private:
	std::vector<size_t> burstTime;//TODO: This should be a bit more complicated including the burst/io
};

