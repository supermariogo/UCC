//CC4 test case- nested statements
//expected result: CC1 3 CC4 2
#include <iostream>
using namespace std;

int main()
{
    int x,y;

    if(x == 1 && y == 1){
        cout << "x = " << x << "y = " << y;

    }


    if(x==1){
        if(y==1){

             cout << "x = " << x << "y = " << y;

        }

    }
}
