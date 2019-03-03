#pragma once
#include <vector>

class Thread
{
public:
    size_t waitingTime;
    size_t lastReadyTime;
    size_t prevBurstTime;
    size_t priority;
    int id;
    bool needsIO; //TODO: impliment IO
    bool finish;
    
    Thread() {
        id = 0;
        waitingTime = 0;
        lastReadyTime = 0;
        prevBurstTime = SIZE_T_MAX;
        priority = 0;
        burstTime.push_back(1); //one time unit of burst
        needsIO = false;
        finish = false;
    }

    Thread(int _id, size_t entryTime, std::vector<size_t> burstT, size_t prior ) {
        id = _id;
        waitingTime = 0;
        lastReadyTime = entryTime;
        prevBurstTime = 0;
        priority = prior;
        burstTime = burstT;
        needsIO = false;
        finish = false;
    }

    ~Thread() {

    }

    void addWaitTime(size_t currTime) {//TODO: recalculates wait time everytime it gets schedualed. potential problem if never gets schedualed. Will we still need wait time in such a case? 
        waitingTime += currTime - lastReadyTime;
        lastReadyTime = currTime;
    }

    //this is public so that CPU can see it but absolutly nothing else should ever look at it
    //back = top of burstTime stack
    std::vector<size_t> burstTime;//TODO: This should be a bit more complicated including the burst/io
    
    bool isFinished(){
        return finish;
    }
};

