#pragma once

#include <chrono>
#include <fstream>
#include <sstream>

class Profiler {
    std::chrono::steady_clock::time_point begin;
    std::stringstream logfile;
        
public: 
    Profiler();
    void start();
    double stop();
    double stop(std::string s);
    void dump();
};

Profiler::Profiler() {
    this->start();
}

void Profiler::start() {
    begin = std::chrono::steady_clock::now();
}

double Profiler::stop(std::string s) {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1e6;
    
    logfile << s << "," << elapsed << std::endl;
    return elapsed;
}

double Profiler::stop() {
    return this->stop("");
}

void Profiler::dump() {
    ofstream myfile;  
    myfile.open("/tmp/Profiler.csv");  
    myfile << logfile.rdbuf();  
    myfile.close();  
}