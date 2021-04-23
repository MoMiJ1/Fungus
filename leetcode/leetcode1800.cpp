#include<bits/stdc++.h>
using namespace std;

// LeetCode 1800. 最大升序子数组

class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int p = 0, res = 0;
        while (p < nums.size()){
            int temp = nums[p];
            while (p < nums.size()-1 && nums[p+1] > nums[p]) temp += nums[++p];
            res = max(res, temp);
            p++;
        }
        return res;
    }
};