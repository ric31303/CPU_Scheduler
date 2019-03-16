#include "json_logging.h"

json_logging::json_logging(std::string path, std::string start){
    
//    result.open(path,std::ios::in);
    std::string fileName = path;
//    int i = 1;
//    while (result.is_open()) {
//        fileName = path + std::to_string(i);
//        result.open(fileName,std::ios::in);
//        i++;
//    }
//    printf("[json_logging] build:%s\n",path.c_str());
    result.open(fileName,std::ios::out);
    result<<"{\n";
    write("strategy",start, false);
}


json_logging::~json_logging()
{
}

void json_logging::write(std::string index,std::string data, bool nodot) {//run this every clock tick
    
    std::string blanks(size, ' ');
    result<<blanks+'"'+index+'"'+":"+'"'+data+'"';
    if (nodot) {
        result<<"\n";
    } else {
        result<<",\n";
    }
}

void json_logging::end() {//run this every clock tick
    result<<"}\n";
    result.close();
}

void json_logging::ThreadsStart() {//run this every clock tick
    commas = false;
    std::string blanks(size, ' ');
    result<<blanks+'"'+"threads"+'"'+":[\n";
}

void json_logging::writeThread(int totalBurstTime, int arriveTime, int priority) {//run this every clock tick
    if (commas) {
        result<<",\n";
    }
    std::string blanks1(size*2, ' ');
    std::string blanks2(size*3, ' ');
    result<<blanks1+"{\n";
    result<<blanks2+'"'+"priority"+'"'+":"+std::to_string(priority)+",\n";
    result<<blanks2+'"'+"arriveTime"+'"'+":"+std::to_string(arriveTime)+",\n";
    result<<blanks2+'"'+"totalBurstAndIOTime"+'"'+":"+std::to_string(totalBurstTime);
    result<<"\n"+blanks1+"}";
    commas = true;
}

void json_logging::ThreadsEnd() {//run this every clock tick
    result<<"],\n";
}

void json_logging::simulationStart() {//run this every clock tick
    commas = false;
    std::string blanks(size, ' ');
    result<<blanks+'"'+"simulations"+'"'+":[\n";
}

void json_logging::writeSimulation(std::vector<int> moveToReadyList, int cycleTime, int moveToCPU, int moveToBlockList, int moveToFinishedList) {//run this every clock tick
    if (commas) {
        result<<",\n";
    }
    std::string blanks1(size*2, ' ');
    std::string blanks2(size*3, ' ');
    result<<blanks1+"{\n";
    result<<blanks2+'"'+"cycleTime"+'"'+":"+std::to_string(cycleTime)+",\n";
    result<<blanks2+'"'+"moveToReadyList"+'"'+":"+"[";
    for (int i =0;i<moveToReadyList.size();i++) {
        result<<std::to_string(moveToReadyList[i]);
        if(i != moveToReadyList.size()-1) {
            result<<",";
        }
    }
    result<<"],\n";
    result<<blanks2+'"'+"moveToCPU"+'"'+":"+std::to_string(moveToCPU)+",\n";
    result<<blanks2+'"'+"moveToBlockList"+'"'+":"+std::to_string(moveToBlockList)+",\n";
    result<<blanks2+'"'+"moveToFinishedList"+'"'+":"+std::to_string(moveToFinishedList)+"\n";
    result<<blanks1+"}";
    commas = true;
}

void json_logging::simulationEnd() {//run this every clock tick
    result<<"],\n";
}

