#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <map>

#include "Scheduler.h"
#include "FIFO_Strategy.h"
#include "SJF_Strategy.h"
#include "SRTF_Strategy.h"
#include "Priority_Strategy.h"
#include "PreemptPriority_Strategy.h"
#include "RR_Strategy.h"
#include "Lottery_Strategy.h"
#include "json_logging.h"

#define Strategy(x) strat = std::make_shared<x>(s->getContext())

void Help(void){
    printf("Scheduler.\n\n");
    printf("Usage:\n");
    printf("\tScheduler   \t FIFO Strategy is used.\n");
    printf("\tScheduler ff\t FIFO Strategy is used.\n");
    printf("\tScheduler rr\t Round Robin Strategy is used.\n");
    printf("\tScheduler sjf\t SJF Strategy is used.\n");
    printf("\tScheduler srtf\t SRTF Strategy is used.\n");
    printf("\tScheduler p\t Priority Strategy is used.\n");
    printf("\tScheduler pp\t Preemtive Priority Strategy is used.\n");
    printf("\tScheduler l\t Lottery Strategy is used.\n\n");
    printf("Options:\n");
    printf("\t-h\t\t Show this screen.\n");
}

int main(int argc, char *argv[]){
    
    std::shared_ptr<CPU> c = std::make_shared<CPU>();
    std::shared_ptr<IO> io = std::make_shared<IO>();
    std::shared_ptr<ScheduleStrategy> strat;
    std::shared_ptr<Scheduler> s = std::make_shared<Scheduler>(c, io, strat);
    // parameters
    std::vector<size_t> burstTimes = {};
    std::string strategyType;
    std::string inputFolder = "tests/";
    std::string outputFolder = "results/";

    std::string fileName = "t5";
    std::string inputFileType = ".txt";
    std::map<std::string, int> m;
    
    
//    m["ff"] = 0; m["rr"] = 1; m["sjf"] = 2; m["srtf"] = 3; m["p"] = 4; m["pp"] = 5; m["l"] = 6;
    // read argc
    if (argc >= 2){
        if (std::string(argv[1]) == "-h"){
            Help();
            return 0;
        }
        switch (atoi(argv[1])) {
            case 0: Strategy(FIFO_Strategy);            strategyType = "FIFO";              break;
            case 1: Strategy(RR_Strategy);              strategyType = "RR";                break;
            case 2: Strategy(SJF_Strategy);             strategyType = "SJF";               break;
            case 3: Strategy(SRTF_Strategy);            strategyType = "SRTF";              break;
            case 4: Strategy(Priority_Strategy);        strategyType = "Priority";          break;
            case 5: Strategy(PreemptPriority_Strategy); strategyType = "PreemptPriority";   break;
            case 6: Strategy(Lottery_Strategy);         strategyType = "Lottery";           break;
            default: Strategy(FIFO_Strategy);           strategyType = "FIFO";              break;
        }
    }else {
        strat = std::make_shared<RR_Strategy>(s->getContext());
        strategyType = "RR";
    }
    if (argc >= 3){
        fileName = argv[2];
    }
    if (argc >= 4){
        inputFolder = argv[3];
    }
    if (argc >= 5){
        outputFolder = argv[4];
    }

    s->updateStrat(strat);

    std::string path = inputFolder+fileName+inputFileType; // default
    std::string outputPath = outputFolder+strategyType+"_"+fileName+".json";

    std::cout<<"input path:"<<path<<std::endl;
    int ThreadsCounter = 0;
    // logging
    std::cout<<"output path:"<<outputPath<<std::endl;
    std::shared_ptr<json_logging> logging = std::make_shared<json_logging>(outputPath,strategyType);
    
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
            burstTimes = {};
            while(getline(linestream,element,',')) {
                if (lineCount == 0) {
                    arrive = stod(element);
                } else if (lineCount == 1) {
                    priority = stod(element);
                } else if (lineCount >= 2) {
                    burst = stod(element);
                    burstTime.push_back(burst);
                    burstTimes.push_back(burst);
                } else {
                    break;
                }
                lineCount++;
            }
            int totalBurstTime = 0;
            for( int i = 0; i < burstTime.size();i++) {
                totalBurstTime = totalBurstTime + burstTime[i];
            }
            
            logging->writeThread(totalBurstTime, arrive, priority);
            std::shared_ptr<Thread> newThread(new Thread(ThreadsCounter, arrive, burstTimes, priority));
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

        
        // check arriveTime
        if(beforeReady->front()!=NULL) {
            while( ThreadsCounter> 0 &&c->getClockTime() >= beforeReady->front()->lastReadyTime) {
                s->addNewThread(beforeReady->front());
                beforeReady->pop_front();
                ThreadsCounter--;
            }
        }
        s->run();
        int * logging_temp = s->getTemp();

        // logging
        logging->writeSimulation(s->getTempReadyList(),logging_temp[0],logging_temp[1],logging_temp[2],logging_temp[3]);

        std::cout <<"   number of finished threads:"<< s->numFinished() << "\n";
        std::this_thread::sleep_for(std::chrono::microseconds(100)); // sleep for 0.1ms
    }
    logging->simulationEnd();
   
    // Calculating average waiting time
    float waitTime = 0;
    float turnaroundTime = 0;
    for (auto& it: *s->getContext()->FinishedList){
        waitTime += it->waitingTime;
        turnaroundTime += (it->finishTime - it->arriveTime);
    }
    waitTime /= s->getContext()->FinishedList->size();
    turnaroundTime /= s->getContext()->FinishedList->size();
    logging->write("avgWatingTime", std::to_string(waitTime), false);
    logging->write("avgTATTime", std::to_string(turnaroundTime), true);
    printf("\nAverage Waiting Time: %f.",waitTime);
    printf("\nAverage turnaround  Time: %f.",turnaroundTime);
//    if( argc >= 2){
//        printf("\nStrategy: %s used.\n",argv[1]);
//    }else {
//        printf("\nStrategy: FIFO used.\n");
//    }
    logging->end();
}
