#include<bits/stdc++.h>
using namespace std;

// LeetCode 1576.替换所有问号

class Solution {
public:
    string modifyString(string s) {
        char a = 'a';
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '?'){
                int k = 0;
                if(i == 0){
                    while (a+k == s[i+1]) k++;
                    s[i] = a + k;
                } else if(i == s.length()-1){
                    while (a+k == s[i-1]) k++;
                    s[i] = a + k;
                } else {
                    while(a+k == s[i-1] || a+k == s[i+1]) k++;
                    s[i] = a + k;
                }
            }
        }
        return s;
    }
};