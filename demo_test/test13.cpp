#include "stdafx.h";
#include <iostream>
using namespace std;

int main()  // CC4=3
{
    for (bool a = true, b = false; a && b; a = false, b = true) {
    	cout << "test logical operator" << endl;
    }

    for (bool a = true, b = false; a == true && b == true; a = false, b = false) {
    	cout << "test deduplication of ==" << endl;
    }
    return 0;
}

int main2()  //CC4=3
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

int main3()  //CC4=2
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


int main4()  //CC4=2
{
    for (bool a = true; a == true; a = false) {
        cout << "test == in for loop" << endl;
    }

    for (bool a = true; a != false; a = false) {
        cout << "test != in for loop" << endl;
    }
    return 0;