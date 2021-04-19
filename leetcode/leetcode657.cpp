#include<bits/stdc++.h>
using namespace std;

// LeetCode 657. 机器人能否返回原点

class Solution {
public:
    bool judgeCircle(string moves) {
        int row = 0, col = 0;
        for(int i = 0; i < moves.size(); i++){
            if(moves[i] == 'R') row++;
            else if(moves[i] == 'L') row--;
            else if(moves[i] == 'U') col++;
            else col--;
        }
        if(row == 0 && col == 0) return true;
        return false;
    }
};