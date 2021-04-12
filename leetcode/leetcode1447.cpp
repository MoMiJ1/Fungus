#include<bits/stdc++.h>
using namespace std;

// LeetCode 1447.最简分数

class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        vector<string> vec;
        if(n == 1) return vec;
        string temp;
        for(int i = 2;i <= n;i++){
            for(int j = 1;j < i;j++){
                if(j == 1 || check(j, i)){
                    temp = to_string(j)+'/'+to_string(i);
                    vec.push_back(temp);
                }
            }
        }
        return vec;
    }
    bool check(int a, int b){
        for(int i = 2;i <= a;i++){
            if(a % i == 0 && b % i == 0) return false;
        }
        return true;
    }
};