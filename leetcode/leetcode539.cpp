#include<bits/stdc++.h>
using namespace std;
# define DAY 1440

// LeetCode 539.最小时间差

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(),timePoints.end());
        int res = 1440;
        for(int i = 0; i < timePoints.size()-1; i++){
            int h1 = atoi(timePoints[i].substr(0,2).c_str());
            int m1 = atoi(timePoints[i].substr(3,2).c_str());
            for(int j = i + 1; j < timePoints.size(); j++){
                if(timePoints[i] == timePoints[j]) return 0;
                int h2 = atoi(timePoints[j].substr(0,2).c_str());
                int m2 = atoi(timePoints[j].substr(3,2).c_str());
                int tmp1 = abs(h2*60+m2-h1*60-m1);
                int tmp2 = DAY - tmp1;
                if(min(tmp1,tmp2) < res) res = min(tmp1,tmp2);
            }
        }
        return res;
    }
};