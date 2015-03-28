//CC4 test case-duplicates
//expected result: CC1 3 CC4 1
#include <iostream>
using namespace std;

int main()
{
     bool flag = false;

     if(flag){
        cout<<"flag = " << flag;
     }

     if(flag == true){
        cout<<"flag = " << flag;
     }

     if(flag == 1){
        cout<<"flag = " << flag;
     }
}
