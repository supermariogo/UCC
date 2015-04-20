//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    bool a = false;
    bool b = true;
    if (a || b) {
    	cout << "a or b is true" << endl;
    }

    if (a == true || b == true) {
    	cout << "b or a is true" << endl;
    }
    return 0;
}
