#include<iostream>
#include<stack>
using namespace std;


bool isValidParanthesis(string expression){
    stack<char> s;
    //Extract each character
    for(char c: expression){

        //if opening bracket,push into the stack
        if(c == '(' || c == '{' || c == '['){
            s.push(c);
        }
         // Condition 1:if closing bracket ,find the corresponding opening bracket
        else{
            //Condition 2:if we encounter a closing bracket but the stack is empty,invalid bracket
            if(!s.empty()){
                //if the expression is valid,the corresponding opening bracket should be at the top of the stack
                if( (c==')' && s.top()=='(' )||
                    (c=='}' && s.top()=='{') ||
                    (c==']' && s.top()=='[' ))
                    {
                    s.pop();
                   }
                else{
                    return false;//if Condition 1 fails
                }

            }
            else{
                return false;//if Condition 2 fails
            }
        }
    }
    return (s.empty())?true:false;
}