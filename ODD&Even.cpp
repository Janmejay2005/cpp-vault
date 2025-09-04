// The reason of writing this code is that I love this code and I think that everyone should know this code 
// This code is to find if the number is even or not and for that we have used different Logic

#include<iostream>
using namespace std;
int main(){
    int num;
    cout<<"Enter your number";
    cin>>num;

    if ((num/2)*2==num)
        cout<<num<<" is even";
    else
        cout<<num<<" is odd";
        return 0;
}
