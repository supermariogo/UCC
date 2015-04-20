//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
	bool a = false;
    while (a != true) {
        cout << "test != in for loop" << endl;
        a = true;
    }

    while (!a) {
        cout << "test deduplication of != in for loop" << endl;
        a = false;
    }
    return 0;
}
