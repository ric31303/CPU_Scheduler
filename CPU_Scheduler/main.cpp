#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Scheduler.h"
#include "FIFO_Strategy.h"
#include "SJF_Strategy.h"
#include "Priority_Strategy.h"


int main(int argc, char *argv[]){
    std::shared_ptr<CPU> c = std::make_shared<CPU>();
    std::shared_ptr<ScheduleStrategy> strat;
    std::shared_ptr<Scheduler> s = std::make_shared<Scheduler>(c, strat);
    strat = std::make_shared<FIFO_Strategy>(s->getContext());
    s->updateStrat(strat);
    
    // parameters
    std::vector<size_t> burstTimes = {2};
    std::string path = "tests/test.txt"; // default
    int ThreadsCounter = 0;
    
    // get file path
    // std::cout<<"input file path:"<<std::endl; // testData/test1.dat
    // std::cin>>path;
    
    std::shared_ptr<std::list<std::shared_ptr<Thread>>> beforeReady =  std::make_shared<std::list<std::shared_ptr<Thread>>>();;
   
    // read test data
    std::ifstream fin;
    fin.open(path);
    if(!fin){
        // no file
        printf("found no file\n");
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
    
    
    printf("Before run cpu, the number of threads:%d\n",ThreadsCounter);
    
    //run scheduler
    while (!s->isFinished() or ThreadsCounter> 0) {
        
        // check arriveTime
        if(beforeReady->front()!=NULL) {
            while( ThreadsCounter> 0 &&c->getClockTime() >= beforeReady->front()->lastReadyTime) {
                s->addNewThread(beforeReady->front());
                beforeReady->pop_front();
                ThreadsCounter--;
            }
        }
        
        s->run();
        std::cout <<"   number of finished threads:"<< s->numFinished() << "\n";
    }

//    int x;
//
//    std::cin >> x;

    //system("pause");
}
