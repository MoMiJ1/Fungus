#include<bits/stdc++.h>
using namespace std;

// LeetCode 面试题 16.10. 生存人数

class Solution {
public:
    int maxAliveYear(vector<int>& birth, vector<int>& death) {
        int live[101] = {0};
        int MAX_year = 0, MAX_nums = 0;

        for (int i = 0; i < birth.size(); i++)
        {
            int start = birth[i], end = death[i];
            for(int j = start-1900;j <= end-1900;j++){
                live[j] += 1;
                if(live[j] > MAX_nums){
                    MAX_year = j + 1900;
                    MAX_nums = live[j];
                } else if(live[j] == MAX_nums && j+1900 < MAX_year){
                    MAX_year = j + 1900;
                }
            }
        }
        return MAX_year;
    }
};