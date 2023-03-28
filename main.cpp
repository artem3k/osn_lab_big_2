#include <cstdio>
#include <deque>
#include <clocale>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Engineer.h"
#include "utility.h"
#define line "\n-----------------------------------\n"

using namespace std;

deque<Engineer> cash = {};
bool file_is_selected = false;
string file_name;

void showEngineer(){
    cout << "Список инженеров:" << endl;
    if(cash.empty()){
        cout << "Список пуст.";
    }
    for (int i = 0; i < cash.size(); i++) {
        cout << i <<  ". " << cash[i].name << " " << cash[i].surname;
    }
    cout << endl;
}

void selectedEngineer(int index){
    if(index == -1){
        return;
    }

    string menu3[] = { "Приказать работать.","Завершить работу инженера.","Посмотреть сколько сделал заданий инженер.","Проверить ,что он работает.","Уволить.","Назад"};
    bool run = true;
    string task;

    do{
        switch (utility::menuWithArray(strdup("Выберете режим работы:"),menu3,6)) {
            case 0:
                if(cash[index].is_work()){
                    cout << line << "У инженера уже занят!" << line;
                }
                else{
                    cout << line << "Введите название задания: ";
                    cin.ignore();
                    getline(cin, task);
                    cout << "Инженер Приступил к работе." << line;
                    cash[index].work(task);
                }
                break;
            case 1:
                cash[index].endWork();
                cout << line << "Инженер завершил работу." << line;
                break;
            case 2:
                cout << line << "Количество сделанных заданий: "<<  cash[index].completed_tasks << line;
                break;
            case 3:
                if(cash[index].is_work()){
                    cout << line;
                    cout << "Инженер " << cash[index].name  << " " << cash[index].surname << " работает над: " << cash[index].task_name;
                    cout << line;
                } else{
                    cout << line;
                    cout << "Инженер " << cash[index].name  << " " << cash[index].surname << " свободен.";
                    cout << line;
                }
                break;
            case 4:
                cash.erase(remove(cash.begin(), cash.end(), 5), cash.end());
                cout << "\nИнженер уволен.\n";
                run = false;
                break;
            case 5:
                run = false;
                break;
        }
    }while(run);
}

int select(){
    int selected = -1;
    if(cash.empty()){
        cout << line << "В списке нет инженеров!" << endl;
        return -1;
    }
    do{
        do{
            showEngineer();
            cout << line << "Выберете инженера: " << endl;
            cout << cash.size() + 1 << " -> " << "Назад " << endl;
            cin >> selected;
        } while (selected < 0 or selected > cash.size() + 1);
        if(selected == cash.size() + 1){
            return -1;
        }
        return selected;
    } while (true);
}

void addEngineer(){
    string name,surname;
    cout << line << "Добавление инженера" << endl;
    cout << "Имя: ";
    cin >> name;
    cout << "Фамилия: ";
    cin >> surname;
    cash.emplace_back(name,surname);
    cout << endl << "Инженер добавлен." << endl;
}

void close_file(){
    file_name = "";
    file_is_selected = false;
    cash = {};
    printf("\nФайл закрыт. \n");
}

void open_file(){
    do{
        printf("Введите имя файла -> \n");
        cin.clear();
        while(cin.get() != '\n');
        cin >> file_name;
        file_name.insert(0,"../");
        ifstream f(file_name.c_str());
        if(f.is_open()){
            f.close();
            goto good;
        }
        printf("Ошибка открытия файла! \n");
    } while (true);
    good:
    file_is_selected = true;
}

void load_file(){
    open_file();
}

void create_file(){
    do{
        printf("Введите имя файла -> \n");
        cin.clear();
        while(cin.get() != '\n');
        cin >> file_name;
        file_name.insert(0,"../");
        ofstream f(file_name.c_str());
        if(f.is_open()){
            f.close();
            goto good;
        }
        printf("Ошибка создания файла! \n");
    } while (true);
    good:
    file_is_selected = true;
}

int main(){
    //Русификация
    #ifdef _WIN32
        system("CHCP 65001"); // UTF-8
    #else
        setlocale(LC_ALL,"RUS");
    #endif

    printf("%s Лабораторная работа номер 2.2 \n Круглый Артём Васильевич \n Гордиенко Максим Артёмович %s", line,line);

    string menu1[] = { "Загрузить файл.","Создать файл.","Завершить программу."};

    string menu2[] = { "Добавить инженера","Список инженеров","Выбрать инженера","Сохранить.","Закрыть файл."};
    do{
        while(!file_is_selected){
            switch (utility::menuWithArray(strdup("Выберете действие"), menu1, 3)) {
                case 0:
                    load_file();
                    break;
                case 1:
                    create_file();
                    break;
                case 2:
                    goto exit;
            }
        }
        //Файл открыт основной цикл программы
        switch (utility::menuWithArray(strdup("Выберете действие"), menu2, 5)) {
            case 0:
                addEngineer();
                break;
            case 1:
                showEngineer();
                break;
            case 2:
                selectedEngineer(select());
                break;
            case 3:

                break;
            case 4:
                close_file();
                break;
        }
    }while(true);

    exit:
        return 0;
}


