#include <algorithm>
#include <iostream>
#include<string>
#include<unordered_map>
#include <memory>
#include <functional>
#include "TaskManager.h"
#include "Command.h"


using AddCommandPtr = std::shared_ptr<AddCommand>;
using DelCommandPtr = std::shared_ptr<DelCommand>;
using UpdateCommandPtr = std::shared_ptr<UpdateCommand>;
using ListCommandPtr = std::shared_ptr<ListCommand>;


int main(){
    
    TaskManager taskmanage;
    
    AddCommandPtr add_command = std::make_shared<AddCommand>(taskmanage); 
    DelCommandPtr del_command = std::make_shared<DelCommand>(taskmanage);
    UpdateCommandPtr update_command = std::make_shared<UpdateCommand>(taskmanage);
    ListCommandPtr list_command = std::make_shared<ListCommand>(taskmanage);
    
    std::unordered_map<std::string, std::function<void(const std::string &)>> commans;
    commans["add"] = [add_command](const std::string & args){
        add_command ->execute(args);
    };
    commans["delete"] = [del_command](const std::string & args){
        del_command ->execute(args);
    };
    commans["list"] = [list_command](const std::string & args){
        list_command ->execute(args);
    };
    commans["update"] = [update_command](const std::string & args){
        update_command ->execute(args);
    };

    /*
     *使用类型擦除技术的注意点：
     * 1.为何要是用智能指针：因为考虑到局部变量的存储期
     * 2.他与crtp使用公共模板的区别在哪里？ 使用公共模板破环了crtp的结构特性，即创建了虚函数表，没有体现出crtp静态联编的特性
     * 3.
     *
     * */




   /* AddCommand addCmd(taskmanage);*/
    /*DelCommand delCmd(taskmanage);*/
    /*UpdateCommand updateCmd(taskmanage);*/
    /*ListCommand listCmd(taskmanage);*/
    
    /*//使用命令模式的设计思想*/
    /*std::unordered_map<std::string, std::unique_ptr<CommandBase>> command;*/
    /*command["add"] = std::make_unique<AddCommand>(taskmanage);*/
    /*command["delete"] = std::make_unique<DelCommand>(taskmanage);*/
    /*command["list"] = std::make_unique<ListCommand>(taskmanage);*/
    /*command["update"] = std::make_unique<UpdateCommand>(taskmanage);*/
    

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
        
        auto it = commans.find(cmd);
        if(it != commans.end()){
            it -> second(args);
        }else
            std::cout << "Unknow instruction" << cmd << std::endl;

    }
    return 0;
}



















