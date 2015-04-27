Truth:

1.

if(a==1 && b=1)  
if "a==1" fails, "b==1" will not be checked.
so different with 
if(b==1){
    if(a==1){}
}
or
if(b==1 && a==)

2. 

if(a==1 || b==1)  

if "a==1" success, "b==1" will not be checked.
so different with 
if(a==1){}
if(b==1){}


assumption/restriction/definition :

1. 
for "&&" , we do logic deduplication , but we donot handle order deduplication 
Example:
	if(a==1 && b==1){}
	equals
	if(a==1){
	if(b==1){}


	if(a==1 && b==1) is different with if(b==1 && a==1)

2. for "||", we handle order deduplication , but not do logic deduplication

	Example:
	if(a==1 || b==1) equals if(b==1 || a==1) equals if(b || a || a!=0)


	if(a==1 || b==1){}
	not equals
	if(a==1){}
	if(b==1){}


    