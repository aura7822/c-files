#include<iostream>
using namespace std;
int main(){
int age;
string name;
cout<<"Enter your name : ";
cin>>name;
cout<<"Enter your age : ";
cin>>age;
if(age<18)
cout<<"Error! you are not allowed to vote";
else
cout<<"you are allowed to vote";
return 0;
}
