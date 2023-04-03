// © Круглый Артём Васильевич, 2023г.
// Утилиты для лаб

#include <iostream>
#include <string>
#include <fstream>
#define line endl << "-----------------------------------" << endl

using namespace std;

namespace utility{
    int menuWithArray(char* msg,string menuElement[],int n){
        int selected = -1;
        do{
            cout << line << msg << line;
            for(unsigned i=0;i<n;i++){
                cout << i << " -> " << menuElement[i] << endl;
            }
            cout << "  -> ";
            cin >> selected;
        } while (selected < 0 or selected >= n);
        cout << "\n";
        return selected;
    }
    int lengthFile(const string& filename){
        char *str = new char [1024];
        int i=0;
        ifstream base(filename);
        while (!base.eof())
        {
            base.getline(str, 1024, '\n');
            i++;
        }
        base.close();
        delete[] str;
        return i;
    }
}

