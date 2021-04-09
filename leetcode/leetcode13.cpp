#include<bits/stdc++.h>
using namespace std;

// LeetCode 13.罗马数字转整数

class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        for(int i = s.size()-1; i >= 0; i--){
            if(i != 0 && values(s[i]) > values(s[i-1])){
                res += (values(s[i]) - values(s[i-1]));
                i--;
            } else {
                res += values(s[i]);
            }
        }
        return res;
    }

    int values(char c) {
        switch (c){
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        }
        return 0;
    }
};