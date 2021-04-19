#include<bits/stdc++.h>
using namespace std;

// LeetCode 27.移出元素

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        for(int i = 0;i<nums.size();i++){
            if(nums[i]!=val){
                nums[k++] = nums[i];
            }
        }
        return k;
    }
};