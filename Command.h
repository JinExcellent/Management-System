#ifndef COMMAND_H_
#define COMMAND_H_

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

class CommandBase{
    public:
        virtual void execute(const std::string & args) = 0;
};

template <typename Derived>
class Command: public CommandBase{
    public:
        void execute(const std::string& args){
            (static_cast<Derived*>(this)) -> executeImpl(args);
        }
};


#include "TaskManager.h"
#include "Task.h"
#include <iostream>


class AddCommand: public Command<AddCommand> { 
    private:
        TaskManager& taskManager;

    public:
        AddCommand(TaskManager& manager): taskManager(manager){ }
        void executeImpl(const std::string& args){
            size_t pos1 = args.find(',');
            size_t pos2 = args.find(',' , pos1 + 1);
            if(pos1 == std::string::npos || pos2 == std::string::npos){
                std::cout << "Wrong format. add <description>,<priority>,<deadline>" << std::endl;
                return;
            }
            std::string description = args.substr(0, pos1);
            int priority = std::stoi(args.substr(pos1 + 1, pos2 - pos1 - 1));
            std::string dueDate = args.substr(pos2 + 1);
            taskManager.AddTask(priority, description, dueDate);
            std::cout << "Successful added" << std::endl;
            return;
        }
};

class DelCommand: public Command<DelCommand> {
    private:
        TaskManager& taskManager;

    public:
        DelCommand(TaskManager& manager): taskManager(manager){ }
        void executeImpl(const std::string& args){
            try{
                size_t pos;
                int id = std::stoi(args , &pos);
                if(pos != args.size()){
                    std::cout << "Wrong format. delete <ID>" << std::endl;
                    return;
                }
                taskManager.DeleteTask(id);
                std::cout << "Successful delete" << std::endl;
            }catch(const std::invalid_argument& e){
                    std::cout << "Wrong format. delete <ID>" << std::endl;
                    return;
            }catch(const std::out_of_range& e){
                    std::cout << "Out of range." << std::endl;
                    return;
            }
        }
};


class ListCommand: public Command<ListCommand>{
    private:
        TaskManager& taskManager;
    
    public:
        ListCommand(TaskManager & manager):taskManager(manager){ }
        void executeImpl(const std::string args){
            int sortOption = 0;
            if(!args.empty()){
                sortOption = std::stoi(args);
            }
            taskManager.ListTasks(sortOption);

        }
};

class UpdateCommand: public Command<UpdateCommand>{
    private:
        TaskManager& taskManager;
    
    public:
        UpdateCommand(TaskManager & manager):taskManager(manager){ }
        void executeImpl(const std::string args){
            size_t pos1 = args.find(',');
            size_t pos2 = args.find(',',pos1 + 1);
            size_t pos3 = args.find(',',pos2 + 1);
        
            if(pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos){
                std::cout << "Wrong format. update <ID>,<description>,<priority>,<deadline>" << std::endl;
                return;
            }
            int id = std::stoi(args.substr(0,pos1));
            std::string description = args.substr(pos1 + 1, pos2 - pos1 -1);
            int priority = std::stoi(args.substr(pos2 + 1, pos3));
            std::string dueDate = args.substr(pos3 + 1);
            taskManager.UpdateTask(id, priority, description, dueDate);
            std::cout << "Successful updated" << std::endl; 

        }
};  
























#endif
