#include<bits/stdc++.h>
using namespace std;

// LeetCode 20. 有效的括号

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        stk.push(s[0]);
        for(int i = 1;i < s.length();i++){
            if(!stk.empty() && check(stk.top(), s[i])) stk.pop();
            else stk.push(s[i]);
        }
        if(!stk.empty()) return true;
        else return false;

    }
    bool check(char a, char b){
        if(a == '(' && b ==')') return true;
        else if(a == '[' && b == ']') return true;
        else if(a == '{' && b == '}') return true;
        else return false;
    }
};

// class Solution {
// public:
//     bool isValid(string s) {
//         if(s.size()==0)return true;
//         stack<char>s_;
//         int i=0;
//         while(s[i]){
//             if(!s_.empty()){
//                 char a=s_.top();
//                 if(s[i]==')'&&a=='(')
//                     s_.pop();
//                 else if(s[i]=='}'&&a=='{')
//                     s_.pop();
//                 else if(s[i]==']'&&a=='[')
//                     s_.pop();
//                 else
//                     s_.push(s[i]);
//             }
//             else
//                 s_.push(s[i]);
//             i++;
//         }
//         return s_.empty();
//     }
// };