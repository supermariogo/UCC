//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    for (bool a = true; a == true; a = false) {
        cout << "test == in for loop" << endl;
    }

    for (bool a = true; a != false; a = false) {
        cout << "test != in for loop" << endl;
    }
    return 0;
}
