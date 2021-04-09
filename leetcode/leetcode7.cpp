#include<bits/stdc++.h>
using namespace std;

// LeetCode 7.整数翻转

class Solution {
public:
    int reverse(int x){
        queue<int> que;
        int temp,count=0;
        long long result=0;
        bool flag = false;
        if(x<0){flag = true;}
        while (x != 0){
            temp = x%10;
            que.push(temp);
            x = x/10;
            count++;
        }
        while (!que.empty()){
            result = result + que.front()*(pow(10,--count));
            que.pop();
        }
        if(result>=pow(2,31)-1 || result<=-pow(2,31)){
            return 0;
        }
        return result;
    }
};