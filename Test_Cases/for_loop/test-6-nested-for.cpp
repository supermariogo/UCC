//CC4 test case
#include "stdafx.h";
#include <iostream>
using namespace std;

int main()
{
	bool a = true;
	bool b = true;
    for (; a && b; a = false, b = false) {

    }

    for (; a; a = false) {
    	for (; b; b = false) {
    		
    	}
    }
    return 0;
}
