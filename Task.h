#ifndef TASK_H_
#define TASK_H_

#include <string>
#include <sstream>
#include <iomanip>


struct Task{
    int id;
    std::string description;
    int priority;
    std::string dueDate;

    std::string ToString() const{
        std::ostringstream oss;

        oss << "ID" << id
            << ", 描述:" << description
            << ", 优先级:" << priority
            << ", 截止日期:" << dueDate;

        return oss.str();
    }
};



#endif
