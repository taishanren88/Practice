   #include <iostream>
   #include <vector>
#include <unordered_map>
#include <cassert>
using namespace std;
   int lengthOfLongestSubstring(string s) {
        int left = 0;
        int right = 0;
        unordered_map<char, int> charCounts;
        auto isRepeating =[&charCounts]()
        {
            for (auto kv : charCounts)
            {
                if (kv.second > 1)
                    return true;
            }
            return false;
        };
        int longestLen = 0;
        while (right < s.size())
        {
            if (charCounts.find(s[right]) == charCounts.end())
                charCounts[s[right]] = 1;
            else
                charCounts[s[right]]++;

            while (isRepeating())
            {
                charCounts[s[left]]--;
                left++;
            }
    
            longestLen = max(longestLen, right - left + 1);
            right++;
        }
        return longestLen;
    }

    int main()
    {
        assert(lengthOfLongestSubstring("abcabcbb")  == 3);
        assert(lengthOfLongestSubstring("bbbbb")  == 1);
        assert(lengthOfLongestSubstring("pwwkew") == 3);
    }