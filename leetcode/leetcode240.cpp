#include<bits/stdc++.h>
using namespace std;

// LeetCode 240. 搜索二维矩阵

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size()-1, col = 0;
        while (row < matrix.size() && col < matrix[0].size())
        {
            if(matrix[row][col] < target){
                col++;
            } else if(matrix[row][col] > target){
                row--;
            } else{
                return true;
            }
        }
        return false;
    }
};