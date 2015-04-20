//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
	bool a = true;
    while (a == true) {
        cout << "test == in for loop" << endl;
        a = false;
    }

    while (a != false) {
        cout << "test != in for loop" << endl;
        a = false;
    }
    return 0;
}
