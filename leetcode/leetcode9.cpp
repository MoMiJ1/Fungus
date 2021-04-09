#include<bits/stdc++.h>
using namespace std;

// LeetCode 9. 回文数

class Solution {
public:
    bool isPalindrome(int x) {
        queue<int> que;
        int count=0;
        long a=0;
        long b = x;
        if (x<0){
            return false;
        }
        while (x!=0){
            que.push(x%10);
            x = x/10;
            count++;
        }
        while (!que.empty()){
            a = a+que.front()*pow(10,--count);
            que.pop();
        }
        if (a-b == 0){ return true;}
        return false;
    }
};