#include<bits/stdc++.h>
using namespace std;

// LeetCode 26.删除有序数组的重复项

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i =  0;
        for (int j = 1; j < nums.size(); j++) {
            if (nums[j] == nums[j-1]){
                j--;
                nums.erase(nums.begin()+j);
            }
        }
        int k = nums.size();
        return k;
    }
};

// LeetCode 27.移除元素

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

// LeetCode 28.实现strstr

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {return 0;}
        int l = needle.size();
        if (l > haystack.size()){return -1;}
        for (int i = 0; i < haystack.size()-l+1; i++) {
            if (haystack.compare(i,l,needle)==0) {
                return i;
            }
        }
        return -1;
    }
};