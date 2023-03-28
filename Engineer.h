//
// Created by Артём  Круглый  on 22.03.2023.
//

#ifndef OSN_LAB_BIG_1_ENGINEER_H

#include <string>
#include <utility>

using namespace std;

class Engineer
{
public:
    Engineer()= default;
    Engineer(string n,string s){
        name = std::move(n); surname = std::move(s);
    }
    Engineer(string n, string s, string task, int com_tasks, bool is_work){
        name = std::move(n);
        surname = std::move(s);
        task_name = std::move(task);
        completed_tasks = com_tasks;
        working = is_work;
    }

//    Engineer(Engineer &engineer) {
//        this->name=engineer.name;
//
//    }

    string name;
    string surname;
    string task_name;

    int completed_tasks = 0;

    void endWork(){
        if(is_work()){
            completed_tasks++;
            task_name = "";
            working = false;
        }
    }
    bool is_work(){
        return working;
    }
    void work(string task){
        endWork();
        task_name = task;
        working = true;
    }
private:
    bool working = false;
};

#define OSN_LAB_BIG_1_ENGINEER_H

#endif //OSN_LAB_BIG_1_ENGINEER_H
