#include<bits/stdc++.h>
using namespace std;

// LeetCode 153.寻找旋转排序数组中的最小值

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while(left < right){
            int mid = left + (right - left) / 2;
            if(nums[mid] > nums[right]){
                left = mid + 1;
            } else if(nums[mid] < nums[right]){
                right = mid;
            } else right--;
        }
        return nums[left];
    }
};