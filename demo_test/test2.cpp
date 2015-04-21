//CC4 test case  
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    bool a = false;

    if(a != 1){
        cout << "a!=1"<<endl;
    }
    if( !a){
        cout << "a is !a" << endl;
    }
    if (a == 0) {
        cout << "a is 0" << endl;
    }

    if (a == false) {
        cout << "a is false" << endl;
    }

    return 0;
}

// CC3=4  CC4=2

int function()
{
    bool flag = false;

    if(flag != 1){
        cout << "a!=1"<<endl;
    }
    if( !flag){
        cout << "a is !a" << endl;
    }
    if (flag == 0) {
        cout << "a is 0" << endl;
    }

    if (flag == false) {
        cout << "a is false" << endl;
    }

    return 0;
}

// CC4 = 2