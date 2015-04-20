//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
    for (bool a = true, b = false; a && b; a = false, b = true) {
    	cout << "test logical operator" << endl;
    }

    for (bool a = true, b = false; a == true && b == true; a = false, b = false) {
    	cout << "test deduplication of ==" << endl;
    }
    return 0;
}
