#include<iostream>
#include<stack>
using namespace std;



void solve(stack<int>s,int x){
    //Base Case:if stack is empty,push the element
    if(s.empty()){
        s.push(x);
    }
    int num=s.top();
    s.pop();

    //Recursive Call
    solve(s,x);

    //while returning
    s.push(num);

}

stack<int> pushAtBottom(stack<int>& myStack,int x){
    solve(myStack,x);
    return myStack;
}