  #include <iostream>
#include <cassert>
using namespace std;
   bool isVowel(char a)
    {
        static const char vowels[] = {'a', 'e', 'i','o','u'};
        for (char c : vowels)
        {
            if (a == c)
                return true;
        }
        return false;
    }
    string reverseVowels(string s) {
        if (s.empty())
            return "";
        int i = 0;
        auto j = s.size() - 1;
        cout << j;
        while (i < j)
        {
            
            if (isVowel(s[i]) && isVowel(s[j]))
            {
                swap(s[i], s[j]);
                i++;
                j--;
            }
            else
            {
                if (!isVowel(s[i]))
                    i++;
                if (!isVowel(s[j]))
                    j--;
            }
        }
        
        return s;
    }
    
      struct ListNode {
    int val;
      ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
  };
        bool hasCycle(ListNode *head) {
        if (!head)
            return false;

        ListNode* slow = head;
        ListNode* fast = head->next;
        while (slow && fast)
        {
            if (fast->val == slow->val)
                return true;
            slow = slow->next;
            fast = fast->next;
            if (fast)
                fast = fast->next;
            else
                break;
        }
        return false;
    }
    
        ListNode *detectCycle(ListNode *head) {
          if (!head)
            return nullptr;

        ListNode* slow = head;
        ListNode* fast = head->next;
        bool hasCycle = false;
        while (slow && fast)
        {
            if (fast == slow)
            {
                hasCycle = true; break;
            }
            slow = slow->next;
            fast = fast->next;
            if (fast)
                fast = fast->next;
            else
                break;
        }
        ListNode* start = head;
        if (!hasCycle)
            return nullptr;

        while (start != fast)
        {
            start = start->next;
            fast = fast->next;
        }
        return start;
    }
    int main()
    {
        assert(reverseVowels("") == "");
    }
