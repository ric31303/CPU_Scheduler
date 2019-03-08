#include <fstream>
#include <vector>
#ifndef _json_logging_
#define _json_logging_
class json_logging
{
public:
    json_logging(std::string,std::string);
    ~json_logging();
    void write(std::string,std::string);
    void ThreadsStart();
    void writeThread(int, int, int);
    void ThreadsEnd();
    void simulationStart();
    void writeSimulation(std::vector<int>, int, int, int, int);
    void simulationEnd();
    void end();
    
private:
    std::fstream result;
    size_t size = 4;
    bool commas = false;
};

#endif
