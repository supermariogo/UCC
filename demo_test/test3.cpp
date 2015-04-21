//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    bool a = false;
    bool b = true;

    if (a == true) {
        if (b == true){
            if(c==true) {
                cout << "a and b is true" << endl;
            }
        }
    }



    if (a == true && b == true && c==true) {
        cout << "a and b is true" << endl;
    }

    return 0;
}



int function2()
{
    bool a = false;
    bool b = true;


    if (a == true && b == true && c==true) {
        cout << "a and b is true" << endl;
    }

    if (a == true) {
        if (b == true){
            if(c==true){
                cout << "a and b is true" << endl;
            }
        }
    }

    if (a == true) {
        if (b == true){
        }

    }


    return 0;
}


int function2()
{
    bool a = false;
    bool b = true;


    if (a == true && b == true && c==true) {
        cout << "a and b is true" << endl;
    }

    if (a == true && b == true){
        if(c==true){
                cout << "a and b is true" << endl;
        }
    }


    return 0;
}