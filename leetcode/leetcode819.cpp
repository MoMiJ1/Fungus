#include<bits/stdc++.h>
using namespace std;

// LeetCode 819. 最常见的单词

class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_map<string,int>mp,ban;
        string res, tmp;
        int cnt = 0;
        for(int i = 0; i < banned.size(); i++){
            ban[banned[i]]++;
        }
        for(int i = 0; i <= paragraph.size(); i++){
            while(isalpha(paragraph[i])) tmp += tolower(paragraph[i++]);
            if(ban[tmp] != 1 && tmp != ""){
                if(cnt < ++mp[tmp]){
                    cnt = mp[tmp];
                    res = tmp;
                }
            }
            tmp.clear();
        }
        return res;
    }
};