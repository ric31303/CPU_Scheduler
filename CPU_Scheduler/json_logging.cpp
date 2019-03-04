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
    printf("[json_logging] build:%s",path.c_str());
    result.open(fileName,std::ios::out);
    result<<"{\n";
    write("strategy",start);
}


json_logging::~json_logging()
{
}

void json_logging::write(std::string index,std::string data) {//run this every clock tick
    
    std::string blanks(size, ' ');
    result<<blanks+'"'+index+'"'+":"+'"'+data+'"';
    result<<",\n";
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

void json_logging::writeThread(int arriveTime) {//run this every clock tick
    if (commas) {
        result<<",\n";
    }
    std::string blanks(size, ' ');
    result<<blanks+"{\n";
    result<<blanks+blanks+'"'+"arriveTime"+'"'+":"+'"'+std::to_string(arriveTime)+'"';
    result<<"\n"+blanks+"}";
   
    commas = true;
}

void json_logging::ThreadsEnd() {//run this every clock tick
    result<<"],\n";
}

//void json_logging::simulationStart() {//run this every clock tick
//    commas = false;
//    std::string blanks(size, ' ');
//    result<<blanks+'"'+"simulations"+'"'+":[\n";
//}
//
//void json_logging::writeSimulation(int *readyList, int,int,int,int) {//run this every clock tick
//
//}
//
//void json_logging::simulationEnd() {//run this every clock tick
//    result<<"],\n";
//}

