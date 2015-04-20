//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    bool a = false;
    bool b = true;

    if (a == true && b == true) {
    	cout << "a and b is true" << endl;
    }

    if (a == true) {
    	if (b == true) {
    		cout << "a and b is true" << endl;
    	}
    }
    return 0;
}
