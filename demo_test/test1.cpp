//CC4 test case  
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()  //CC4= 2
{
    bool a = false;

    if(a == 1){
        cout << "a!=1"<<endl;
    }
    if( a==1){
        cout << "a is !a" << endl;
    }

    // if (a == 0) {
    //  cout << "a is 0" << endl;
    // }
    return 0;
}

int function2() //CC4=2
{
    bool a = false;

    if(a == 1){
        cout << "a!=1"<<endl;
    }
    if( a==1){
        cout << "a is !a" << endl;
    }

    if( a==1){
        cout << "a is !a" << endl;
    }

    return 0;
}


// CC3=4  CC4=2