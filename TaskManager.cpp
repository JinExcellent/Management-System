#include "TaskManager.h"
#include "Logger.h"
#include "Task.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

TaskManager::TaskManager(): NexId(1){
    LoadTasks();
}

void TaskManager::AddTask(int priority, const std::string description, const std::string dueDate){
    Task task;

    task.id = NexId++;
    task.priority = priority;
    task.description = description;
    task.dueDate = dueDate;

    tasks.push_back(task);
    Logger::GetInstance().log("添加任务:" + task.ToString());
    SaveTasks();
}

void TaskManager::DeleteTask(int id){

    //******************************需要学习语法********************/
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task){
        return task.id == id;
    });

    if(it != tasks.end()){
        Logger::GetInstance().log("Delete task:" + it->ToString());
        tasks.erase(it);
        SaveTasks();
    }else{
        std::cout << "Not found id:" << id << "'s task." << std::endl;
    }
}


void TaskManager::UpdateTask(int id, int priority, const std::string description, const std::string dueDate){
    for(auto& task : tasks){
        if(task.id == id){
            Logger::GetInstance().log("Before updating:" + task.ToString());
            task.description = description;
            task.dueDate = dueDate;
            task.priority = priority;
            Logger::GetInstance().log("After updating:" + task.ToString());
            SaveTasks();
            return;
        }
    }
    std::cout << "Not found id:" << id << "'s task." << std::endl;
}

void TaskManager::ListTasks(int sortoption) const{
    std::vector<Task> SortTask = tasks;

    switch (sortoption) {
        case 1:
            std::sort(SortTask.begin(), SortTask.end(), CompareByPriority);
            break;
        case 2: 
            std::sort(SortTask.begin(), SortTask.end(), CompareByDeDate);
            break;
        default:
            break;
    }

    for(auto& task : tasks)
        std::cout << task.ToString() << std::endl;
        
    Logger::GetInstance().log("Show task table.\n");
}

void TaskManager::LoadTasks(){
    std::ifstream ifs("tasks.txt" , std::ios::in);
    if(!ifs.is_open()){
        Logger::GetInstance().log("Not found file tasks.txt and create a new file.\n");
        return;
    }

    std::string line;
    while(std::getline(ifs , line)){
        std::istringstream iss(line);
        Task task;
        char delimter;
        
        iss >> task.id >> delimter;
        std::getline(iss, task.description, ',');      //两种读取输入字符的方式
        iss >>  task.priority >> delimter;
        iss >> task.dueDate;
        tasks.push_back(task);
        if(task.id >= NexId){
            NexId = task.id + 1;
        }
    }
    ifs.close();
    Logger::GetInstance().log("Load successful:");
}

void TaskManager::SaveTasks() const{
    std::ofstream ofs("tasks.txt" , std::ios::out); 

    if(!ofs.is_open()){
        std::cout << "Unable open to file tasks.txt\n";
        return;
    }
    for(auto& task : tasks){
        ofs << task.id << "," << task.description << "," << task.priority << "," << task.dueDate << "\n";
    }

    Logger::GetInstance().log("Save successful.\n");
    ofs.close();
}


bool TaskManager::CompareByPriority(const Task& a, const Task& b){
    return a.priority <= b.priority;    
}
     
bool TaskManager::CompareByDeDate(const Task& a, const Task& b){
    return a.dueDate < b.dueDate;
}


























