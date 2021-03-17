#include<bits/stdc++.h>
using namespace std;

// LeetCode 2.两数相加

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr, *temp = head;
        int carry = 0, sum = 0;
        while(l1 != nullptr || l2 != nullptr || carry == 1)
        {
            if(l1 != nullptr){
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2 != nullptr){
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            if(!head) {
                head = temp = new ListNode(sum%10);
                carry = sum/10;
            } else {
                temp->next = new ListNode(sum%10);
                carry = sum/10;
                temp = temp->next;
            }
            sum = 0;
        }
        return head;
    }
};
