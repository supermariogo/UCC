//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    bool a = false;
    bool b = true;
    bool c = true;

    if ((b || a) && c) {
    	cout << "a or b is true and c is true" << endl;
    }

    return 0;
}
