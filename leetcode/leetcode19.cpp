#include<bits/stdc++.h>
using namespace std;

// LeetCode 19. 删除链表的倒数第 N 个结点

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *tower = new ListNode(0,head);
        ListNode *fast = head, *slow = tower;
        for(int i = 0;i < n;i++){
            fast = fast->next;
        }
        while(fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        ListNode *res = tower->next;
        delete tower;
        return res;
    }
};