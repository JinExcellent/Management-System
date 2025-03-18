#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include <vector>
#include <string>

#include "Task.h"
class TaskManager{
    private:
        std::vector<Task> tasks;
        int NexId;

        //辅助函数
        static bool CompareByPriority(const Task& a, const Task& b);
        static bool CompareByDeDate(const Task& a, const Task& b);

    public:
        TaskManager();

        void AddTask(int priority, const std::string description, const std::string dueDate);
        void DeleteTask(int id);
        void UpdateTask(int id, int priority, const std::string description, const std::string dueDate);
        void ListTasks(int sortOption = 0) const;
        void LoadTasks();
        void SaveTasks() const;
};

#endif
