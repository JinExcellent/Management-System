#include "Logger.h"
#include <chrono>
#include <ctime>
#include <mutex>
#include <iostream>


Logger& Logger::GetInstance(){
    static Logger instance;
    return instance;
}

Logger::Logger(){
    LogFile.open("log.txt" , std::ios::app);

    if(!LogFile.is_open()){
        std::cerr << "Not find log.txt" << std::endl;
    }
}

Logger::~Logger(){
    if(LogFile.is_open())
        LogFile.close();
}


void Logger::log(const std::string &message){
    std::lock_guard<std::mutex> lock(mtx);
    if(LogFile.is_open()){
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        LogFile << std::ctime(&now_time) << ":" << message << std::endl;
    }
}

