#include<iostream>
#include"stack_vector.h"
using namespace std;
int main()
{
    stack<int> s;
    s.push(10);
    cout<<s.pop()<<endl;
    s.push(38);
    s.top()=19;
    cout<<s.top()<<endl;

    return 0;
}