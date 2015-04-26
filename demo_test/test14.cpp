int main()  //cc4=3
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

int main2()  //cc4=3
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



int main3() //cc4=2
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


int main4() //cc4=2
{
    bool a = true;
    while (a == true) {
        cout << "test == in for loop" << endl;
        a = false;
    }

    while (a != false) {
        cout << "test != in for loop" << endl;
        a = false;
    }
    return 0;
}