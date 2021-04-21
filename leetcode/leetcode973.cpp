#include<bits/stdc++.h>
using namespace std;

// LeetCode 973.最接近原点的K个点

class Solution {
public:
    struct elem
    {
        vector<int> point;
        int dist;
        friend bool operator < (elem e1, elem e2) {
            return e1.dist >= e2.dist;
        }
    };
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<elem> pq;
        vector<vector<int>>res;
        for(int i = 0; i < points.size(); i++){
            int temp = pow(points[i][0],2) + pow(points[i][1],2);
            pq.push({points[i],temp});
        }
        for(int i = 0; i < k; i++){
            res.push_back(pq.top().point);
            pq.pop();
        }
        return res;
    }
};