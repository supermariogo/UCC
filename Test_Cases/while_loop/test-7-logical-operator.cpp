//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
	bool a = true, b = false;
    while (a && b) {
    	cout << "test logical operator" << endl;
    	a = false;
    	b = false;
    }

    while (a == true && b == true) {
    	cout << "test deduplication of ==" << endl;
    	a = false;
    	b = false;
    }
    return 0;
}
