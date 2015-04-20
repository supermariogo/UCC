//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    bool a = false;
    bool b = true;
    bool c = true;

    if (a == true && b == true && c == true) {
    	cout << "a and b is true" << endl;
    }

    if (a == true) {
    	if (b == true) {
    		if (c == true) {
                cout << "a and b and c are true" << endl;
            }
    	}
    }
    return 0;
}
