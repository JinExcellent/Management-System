#include <algorithm>
#include <iostream>
#include<string>
#include<unordered_map>
#include <memory>
#include "TaskManager.h"
#include "Command.h"


int main(){
    
    TaskManager taskmanage;

    AddCommand addCmd(taskmanage);
    DelCommand delCmd(taskmanage);
    UpdateCommand updateCmd(taskmanage);
    ListCommand listCmd(taskmanage);
    
    //使用命令模式的设计思想
    std::unordered_map<std::string, std::unique_ptr<CommandBase>> command;
    command["add"] = std::make_unique<AddCommand>(taskmanage);
    command["delete"] = std::make_unique<DelCommand>(taskmanage);
    command["list"] = std::make_unique<ListCommand>(taskmanage);
    command["update"] = std::make_unique<UpdateCommand>(taskmanage);
    

    std::cout << "Management system" << std::endl;
    std::cout << "Usable instraction: add delete list update" << std::endl;

    std::string input;
    while(true){
        std::cout << ">\n";
        std::getline(std::cin, input);
        if(input.empty())   continue;

        //分离指令和参数
        size_t spacePos = input.find(' ');
        std::string cmd = input.substr(0, spacePos);
        std::string args;

        if(spacePos != std::string::npos){
            args = input.substr(spacePos + 1);
        }

        if(cmd == "exit"){
            std::cout << "quit" << std::endl;
            break;
        }
        
        auto it = command.find(cmd);
        if(it != command.end()){
            it -> second -> execute(args);
        }else
            std::cout << "Unknow instruction" << cmd << std::endl;

    }
    return 0;
}



















