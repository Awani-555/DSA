#include<iostream>
#include<stack>
using namespace std;

bool findRedundantBrackets(string &s)
{
    stack<char> st;

    for(char ch:s)
    {

        //opening brackets and operators are pushed into the stack
        if(ch == '(' || ch == '+' ||ch == '-' || ch == '*' || ch == '/'){
            st.push(ch);

        }
        else{
            //either lowercase letters or closing bracket
            if(ch==')'){
                bool isRedundant=true;
                
                while(st.top()!='(')
                {
                    //if there is an operator between opening and closing bracket then the bracket isn't redundant
                    if(st.top()=='+'||st.top()=='-'||st.top()=='*'||st.top()=='/'){
                    isRedundant=false;
                    }
                    //keep removing elements till we find the corresponding opening bracket
                    st.pop();
                }
                  if(isRedundant == true)
                    return true;
                    st.pop();//remove opening bracket 
            }

        }
    }
    return false;
};
