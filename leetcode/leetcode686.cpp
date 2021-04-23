#include<bits/stdc++.h>
using namespace std;

// LeetCode 686. 重复叠加字符串匹配

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        if(a.empty() || b.empty()) return -1;
        int res = 1;
        string temp = a;
        int aSize = a.size(), bSize = b.size();
        while (temp.find(b) == string::npos)
        {
            if(temp.size() > aSize * 2 + bSize) return -1;
            temp += a;
            res++;
        }
        return res;
    }
};