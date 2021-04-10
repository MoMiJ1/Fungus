#include<bits/stdc++.h>
using namespace std;

// LeetCode 15.三数之和

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        // 特判
        if(nums.size()<3) return res;
        sort(nums.begin(), nums.end());
        int i = 0;
        // 只要搜索到数组的倒数第三个就可以了，之后凑不齐3个数了
        while (i < nums.size()-2)
        {
            if(nums[i] > 0) return res;
            int left = i+1, right = nums.size()-1;
            while (left < right)
            {
                if(nums[i]+nums[left]+nums[right] == 0){
                    res.push_back({nums[i],nums[left],nums[right]});
                    while(left < right && nums[left] == nums[left+1]){
                        left++;
                    }
                    while(left < right && nums[right] == nums[right-1]){
                        right--;
                    }
                    left++;
                    right--;
                } else if(nums[i]+nums[left]+nums[right] < 0){
                    left++;
                } else right--;
            }
            while(i < nums.size()-2 && nums[i] == nums[i+1]){
                i++;
            }
            i++;
        }
        return res;
    }
};

