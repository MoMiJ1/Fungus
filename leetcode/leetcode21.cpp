#include<bits/stdc++.h>
using namespace std;

// LeetCode 21. 合并链表

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
       ListNode *head = new ListNode(1);
        ListNode *ret = head;
        while (l1 != NULL && l2 != NULL){
            if (l1->val <= l2->val){
                ret->next = l1;
                l1 = l1->next;
            } else{
                ret->next = l2;
                l2 = l2->next;
            }
            ret = ret->next;
        }
        ret->next = l1 == NULL ? l2 : l1;
        return head->next;
    }
};