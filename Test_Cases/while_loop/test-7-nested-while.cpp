//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
	bool a = true;
	bool b = true;
    while (a && b) {
        a = false;
        b = false;
    }

    while (a) {
    	while (b) {
            b = false;
        }
        a = false;
    }
    return 0;
}
