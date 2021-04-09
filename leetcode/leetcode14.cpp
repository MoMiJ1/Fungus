#include<bits/stdc++.h>
using namespace std;

// LeetCode 14.最长公共子串

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0) return "";
        string res = "", first = strs[0];
        char c;
        for(int i = 0;i < first.length();i++){
            c = first[i];
            for(int j = 1;j < strs.size();j++){
                if(i == strs[j].length() || strs[j][i] != c){
                    return res;
                }
            }
            res += c;
        }
        return res;
    }
};