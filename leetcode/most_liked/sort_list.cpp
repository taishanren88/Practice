#include <iostream>
#include <vector>
#include <cassert>
#include "utils.h"
using namespace std;

 ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        // Find the midpoint of the list (use fast, slow)
        // Consider [start, slow -1] as left, [slow, end] as right
        // Sort everything from the left up to this point
        // Mark (slow -1 ) -> net = nullptr temporarily
        // Sort the right list
        // Merge the two results using two pointer solution
        // take a dummy node, and update its next pointer acccordingly
        // dummy->next
        auto slow = head;
        ListNode* prev = nullptr;
        auto fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }
        if (prev) {
            prev->next = nullptr;
        }

        auto left = sortList(head);
        auto right = sortList(slow);
        // Merge
        ListNode dummyNode (0);
        auto dummyItr = &dummyNode;
        while (left && right) {
            if (left->val <= right->val) {
                dummyItr->next = left;
                left = left->next;
            } else {
                dummyItr->next = right;
                right = right->next;
            }
            dummyItr = dummyItr->next;
        }
        while (left) {
            dummyItr->next = left;
            left = left->next;
            dummyItr = dummyItr->next;
        }
        while (right) {
            dummyItr->next = right;
            right = right->next;
            dummyItr = dummyItr->next;
        }

        return dummyNode.next;
    }

int main() {
    assert(toVector(sortList(toList({2,1}))) == vector<int>({1,2}));
    assert(toVector(sortList(toList({2,1,3}))) == vector<int>({1,2, 3}));
    assert(toVector(sortList(toList({4,2,1,3}))) == vector<int>({1,2, 3,4}));
    assert(toVector(sortList(toList({-1,5,3,4,0}))) == vector<int>({-1,0,3,4,5}));
}
