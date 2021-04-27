#include<bits/stdc++.h>
using namespace std;

// LeetCode 880. 索引处的解码字符串

/*
思路：
1.首先遍历整个字符串，记录最终字符串的长度：
    若当前解析出的字符串长度 < K,继续解析；
    若 > K,停止解析
2. 当前字符串长度为 sum>K
    从停止解析前最后遍历的字符 S[i] 开始回退：
        若该字符c为数字，则 sum/c（因为说明总长度遇到这个数字后重复了c遍）
            若 sum/c < K，说明第 K位在 sum/c ~ sum这段区间内，且结果字符存在于 sum/c这段字符串内；
                则 K %= (sum/c) ，如果 K=0，则退出搜索，结果为 S[i]
        若该字符c为字母，则 sum--
        i--
    当前字符串长度 sum == K，退出搜索，结果为 S[i]
3. 

*/

class Solution {
public:
    string decodeAtIndex(string S, int K) {
        string ans;
        int n = S.length();
        long sum = 0, i = 0; 
        for (; i < n; i++) { 
            if (isalpha(S[i])) sum++;
            else { sum *= (S[i] - '0'); }
            if (sum >= K) break;
        }
        for (; i >= 0; i--) {
            if (sum > K){
                if (isdigit(S[i])) {
                    sum /= (S[i] - '0');
                    if (K > sum){
                        K %= sum;
                        if (K == 0) break;
                    }
                } else sum--;
            } else if (sum == K) break;
        }
        while (isdigit(S[i])) i--;
        ans += S[i];
        return ans;
    }
};