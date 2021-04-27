#include<bits/stdc++.h>
using namespace std;

// LeetCode 938. 二叉搜索树的范围和

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void midOrder(TreeNode *root,vector<int> &res){
        if(!root) return;
        midOrder(root->left, res);
        res.push_back(root->val);
        midOrder(root->right, res);
    }
    int rangeSumBST(TreeNode* root, int low, int high) {
        int cnt = 0;
        vector<int> vec;
        midOrder(root,vec);
        for(int i = 0; i < vec.size() && vec[i] <= high; i++){
            if(vec[i] >= low){
                cnt += vec[i];
            }
        }
        return cnt;
    }
};

class Solution {
public:
    int cnt = 0, l, h;
    void midOrder(TreeNode *root){
        if(!root) return;
        midOrder(root->left);
        if(root->val >= l && root->val <= h){
            cnt += root->val;
        } else if(root->val > h) return;
        midOrder(root->right);
    }
    int rangeSumBST(TreeNode* root, int low, int high) {
        l = low, h = high;
        midOrder(root);
        return cnt;
    }
};