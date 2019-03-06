#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>

#include "Scheduler.h"
#include "FIFO_Strategy.h"
#include "SJF_Strategy.h"
#include "SRTF_Strategy.h"
#include "Priority_Strategy.h"
#include "PreemptPriority_Strategy.h"
#include "RR_Strategy.h"
#include "Lottery_Strategy.h"
#include "json_logging.h"

int main(int argc, char *argv[]){
    
    std::shared_ptr<CPU> c = std::make_shared<CPU>();
    std::shared_ptr<ScheduleStrategy> strat;
    std::shared_ptr<Scheduler> s = std::make_shared<Scheduler>(c, strat);
    strat = std::make_shared<FIFO_Strategy>(s->getContext());
    s->updateStrat(strat);
    
    // logging
    std::string outputPath = "results/new_test10.json";
    std::shared_ptr<json_logging> logging = std::make_shared<json_logging>(outputPath,"FIFO");

    // parameters
    std::vector<size_t> burstTimes = {2};
    std::string path = "tests/test_size10.txt"; // default
    int ThreadsCounter = 0;
    
    // get file path
    // std::cout<<"input file path:"<<std::endl; // testData/test1.dat
    // std::cin>>path;
    
    std::shared_ptr<std::list<std::shared_ptr<Thread>>> beforeReady =  std::make_shared<std::list<std::shared_ptr<Thread>>>();;
   
    // read test data
    logging->ThreadsStart();
    std::ifstream fin;
    fin.open(path);
    if(!fin){
        // no file
        printf("[main] found no file\n");
        return 0;
    } else {
        std::string line;
        
        while(getline(fin,line,'\n')){
            std::vector<int> burstTime;
            std::stringstream linestream(line);
            std::string element;
            int lineCount = 0;
            int arrive = 0, priority = 1;
            size_t burst = 0;
            
            // read each line, assume each line only has [arriveTime,priority, burstTime]
            while(getline(linestream,element,',')) {
                if (lineCount == 0) {
                    arrive = stod(element);
                    logging->writeThread(arrive);
                } else if (lineCount == 1) {
                    priority = stod(element);
                } else if (lineCount == 2) {
                    burst = stod(element);
                } else {
                    break;
                }
                lineCount++;
            }
            burstTimes = {burst};
            std::shared_ptr<Thread> newThread(new Thread(ThreadsCounter,arrive,burstTimes,priority));
            beforeReady->push_back(newThread);
            ThreadsCounter++;
        }
        
    }
    fin.close();
    logging->ThreadsEnd();
    
    
    //run scheduler
    printf("[main] Before run cpu, the number of threads:%d\n",ThreadsCounter);
    logging->simulationStart();
    while (!s->isFinished() or ThreadsCounter> 0) {
        
        int initialPointer = 10;
        int * moveReadyList = &(initialPointer);;
        int readyCounter = 0;
        // check arriveTime
        if(beforeReady->front()!=NULL) {
            while( ThreadsCounter> 0 &&c->getClockTime() >= beforeReady->front()->lastReadyTime) {
                s->addNewThread(beforeReady->front());
                // write temp for logging
                *(moveReadyList+readyCounter) = beforeReady->front()->id;
                printf("    test pointer threads:%d\n",*(moveReadyList+readyCounter));
                beforeReady->pop_front();
                ThreadsCounter--;
                readyCounter++;
            }
        }
        s->run();
        int * logging_temp = s->getTemp();
        // log testing
        int n = 3;
        int* numberArray = new int[n];
        for (int i = 0; i < n; i++) {
            numberArray[i] = i;
        }
        logging->writeSimulation(moveReadyList,readyCounter,logging_temp[0],logging_temp[1],logging_temp[2],logging_temp[3]);
        // log testing
        
        std::cout <<"   number of finished threads:"<< s->numFinished() << "\n";
        std::this_thread::sleep_for(std::chrono::microseconds(1000)); // sleep for 1ms
    }
    logging->simulationEnd();
    logging->end();
//    int x;
//
//    std::cin >> x;

    //system("pause");
}
