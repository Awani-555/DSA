#include<iostream>
#include<stack>
using namespace std;

int main(){
    string str="Malcolm in the Middle";
    stack<char> s;
     for(char c: str)
     {
        s.push(c);
     }
     string ans="";

     while(!s.empty())
     {
        ans.push_back(s.top());
        s.pop();
     }
    cout << "answer is: "<< ans << endl;
    return 0;
}
/*
Reverse a string using Stack
*Push all the characters in the string to a stack
*Empty the stack by popping the top and adding it to a string
Time Complexity:O(n)
Space Complexity:O(n)
*/