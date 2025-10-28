#include<iostream>
#include<stack>
using namespace std;


void insertAtBottom(stack<int>s,int x){
    //Base Case:if stack is empty,push the element
    if(s.empty()){
        s.push(x);
    }
    int num=s.top();
    s.pop();

    //Recursive Call
    insertAtBottom(s,x);

    //while returning
    s.push(num);

}


void reverseStack(stack<int>& st){
    //Base camp
    if(st.empty()) return;

    int num=st.top();
    st.pop();

    //recursive call
    reverseStack(st);

    //while returning
    insertAtBottom(st,num);
    

}