#ifndef LOGER_H_
#define LOGER_H_

#include <string>
#include <fstream>
#include <mutex>

class Logger{
    private:
        Logger();
        ~Logger();

        std::ofstream LogFile;
        std::mutex mtx;
    public:
        static Logger& GetInstance();
        
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        //记录日志
        void log(const std::string & message);

};

#endif
