#pragma once
#include <memory>
#include <list>

#include "Thread.h"

class IO
{
public:
    IO();
    IO(std::shared_ptr<std::list<std::shared_ptr<Thread>>> ioList);
    ~IO();
    
    std::shared_ptr<Thread> run();//run this every clock tick
    bool getStatus();
    void setWorkingThread(std::shared_ptr<Thread> thread);
    std::shared_ptr<Thread> getWorkingThread();

private:
    std::shared_ptr<std::list<std::shared_ptr<Thread>>> IOList = NULL;
    std::shared_ptr<Thread> currThread = NULL;
    size_t burstTimeLeft = 0;

};

