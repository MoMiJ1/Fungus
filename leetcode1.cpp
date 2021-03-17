#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> mp; // first是值，second是索引
        vector<int> res;
        int pair;
        for (int i = 0; i < nums.size(); i++)
        {
            pair = target - nums[i];
            map<int, int>::iterator iter = mp.find(pair);
            if(iter != mp.end()){
                res.push_back(iter->second);
                res.push_back(i);
                break;
            } else {
                mp[nums[i]] = i;
            }
        }
        return res;
    }
};