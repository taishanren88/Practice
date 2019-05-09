#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


/**
 * Definition for singly-linked list.
 */
  struct ListNode {
     int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* last = nullptr;
        ListNode * root = nullptr;
        int carry = 0;
        while ( (l1 != nullptr || l2 != nullptr) || carry != 0)
        {
            auto l1Curr = l1 ? l1->val : 0;
            auto l2Curr = l2 ? l2->val : 0;
            auto result = l1Curr + l2Curr + carry;
            auto sum = result % 10;
            carry = result / 10;
            auto node =  new ListNode(sum);
            cout << node->val << ",";
            if (root == nullptr) {
                last = node;
                root = node;
            }
            else {
                last->next = node;
                last = last->next;
            }
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        cout << endl;
        return root;
    }

int main()
{
    auto generateList = [](const vector<int>& a)
    {
        ListNode* root = nullptr;
        ListNode* last = nullptr;
        for (auto num : a)
        {
            auto node = new ListNode(num);
            if (root == nullptr)
            {
                root = node;
                last = root;
            }
            else
            {
                last->next = node;
                last = last->next;
            }
        }
        return root;
    };

    auto degenerateList = [](ListNode* l)
    {
        vector<int> results;
        while (l != nullptr)
        {
            results.push_back(l->val);
            l = l->next;
        }
        return results;
    };

    assert(degenerateList(addTwoNumbers(generateList({2,4,3}), generateList({5,6,4}))) == vector<int>({7, 0, 8}));
    assert(degenerateList(addTwoNumbers(generateList({1, 8}), generateList({0}))) == vector<int>({1, 8}));

}