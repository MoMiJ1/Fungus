#include<bits/stdc++.h>
using namespace std;

// LeetCode 3.无重复最长子串

// Solution 1
// 从第一位扫描，每次将未出现过的字符保存进 map
// 当发现重复字符，更新最大长度，从该重复字符第一次出现的位置的下一位开始扫描
// 这么写结果的 时间复杂度、空间复杂度都很高
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s == "") return 0;
        map<char,int> mp; // 字符、索引
        int res = 0, MAX_Length = 0, i = 0;
        int length = s.size();
        while (i < length) {
            map<char,int>:: iterator iter = mp.find(s[i]);
            if (iter != mp.end()) { // 出现重复字符
                i = iter->second + 1;
                mp.clear();
                MAX_Length = max(res, MAX_Length);
                res = 0;
            } else {
                mp[s[i]] = i;
                res += 1;
                i++;
            }
        }
        return max(res, MAX_Length);
    }
};

// Solution 2
// 采用滑动窗口
/* 
    s：输入的字符串
    i：最长子字符串的起点数组下标
    j：最长子字符串的终点数组下标
    ans：最长子字符串长度
    str[]：下标(序号)表示 "字符"，储存的值表示该字符位置+1
*/
int lengthOfLongestSubstring(string s) {
    vector<int> str(128,0); // 初始将所有值都设为0
    int i = 0, ans = 0;
    for (int j = 0;j < s.size();j++) // 在整个字符串长度之内
    {
        /* 
        1.如果当前字符在之前没出现过，那么其值肯定是0，不会改变当前扫描起点
        2.如果s[j]出现过，则其值一定大于0：如果起点i小于str[s[j]]，说明重复的字符在当前的子串内，
        此时应该切换扫描起点至s[j]上一次出现位置的下一位(str[s[j]]储存的值)，重新扫描
        */
        i = max(i, str[s[j]]);  
        str[s[j]] = j + 1; // 当前字符的坐标更新
        ans = max(ans, j-i+1); // 比较哪个距离更大
    }
    return ans;
}