#include<iostream>
#include<stack>
using namespace std;

    void solve(stack<int>&inputStack,int count,int size){
        //Base Case:When we reach the middle of the node,we remove it and go back
        if(count==size/2)
        {
            inputStack.pop();
            return;
        }
        // If it is not the middle node just save the top in num and then remove it and move to the next node
        int num=inputStack.top();
        inputStack.pop();

        //Recursive Call
        solve(inputStack,count++,size);

        //On the way back ,push num back
        inputStack.push(num);
    }

    void deleteMiddle(stack<int>&inputStack,int N){
        int count=0;
         solve(inputStack, count, N);
    }