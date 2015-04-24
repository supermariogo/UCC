int main()  // cc4 is 5
{
    bool a = false;
    bool b = true;

    if(a==1 && b==1){
    	if(c==1){
        	cout<<"worng"<<endl;
        }
    }

    if(b==1 && b==1){
    	if(d==1){
        	cout<<"worng"<<endl;
        }

    }

    if(a==1 && b==1){
        if(c==1 || d==1){
            cout<<"worng"<<endl;
        }
    }


}