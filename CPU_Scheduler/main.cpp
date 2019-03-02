#include <iostream>
#include <vector>
#include <fstream>
#include "Scheduler.h"
#include "FIFO_Strategy.h"


int main(int argc, char *argv[]){
	std::shared_ptr<CPU> c = std::make_shared<CPU>();
	std::shared_ptr<ScheduleStrategy> strat;
	std::shared_ptr<Scheduler> s = std::make_shared<Scheduler>(c, strat);
    strat = std::make_shared<FIFO_Strategy>(s->getContext());
    s->updateStrat(strat);

    // test
    std::vector<size_t> burstTimes = {3,4,5};
    
    for (int i = 0; i < 10; i++) {
//        std::shared_ptr<Thread> newThread(new Thread());
        printf("%d\n",i);
        std::shared_ptr<Thread> newThread(new Thread(i,burstTimes));
        s->addNewThread(newThread);
    }
    
    // get file path
//    std::string path;
//    std::cout<<"input file path:"<<std::endl; // testData/test1.dat
//    std::cin>>path;
//    

//    while (!s->isFinished()) {
//        s->run();
//
//    std::cout << s->numFinished() << "\n";
//    }

//    int x;
//
//    std::cin >> x;

	//system("pause");
}
