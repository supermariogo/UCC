//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
	bool a = false;
    for (; a != true; a = true) {
        cout << "test != in for loop" << endl;
    }

    for (; !a; a = true) {
        cout << "test deduplication of != in for loop" << endl;
    }
    return 0;
}
