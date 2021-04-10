#include<bits/stdc++.h>
using namespace std;

// LeetCode 16.最接近的三数之和

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 20000;
        sort(nums.begin(), nums.end());
        int i = 0;
        while (i < nums.size())
        {
            int left = i+1, right = nums.size()-1;
            while(left < right)
            {
                int temp = nums[i] + nums[left] + nums[right];
                if(abs(temp-target) < abs(res-target)){
                    res = temp;
                }
                if(temp == target){
                    i = nums.size();
                    break;
                } else if(temp > target){
                    right--;
                } else left++;
            }
            while(i < nums.size()-2 && nums[i] == nums[i+1]){i++;}
            i++;
        }
        return res;
    }
};