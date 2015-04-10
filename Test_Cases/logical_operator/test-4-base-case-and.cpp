//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    bool a = false;
    bool b = true;
    bool c = true;

    if (a && b) {
    	cout << "a and b is true" << endl;
    }

    if (a == true && b == true) {
    	cout << "a and b is true" << endl;
    }
    return 0;
}
