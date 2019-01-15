#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

int longestWithK(const string& s, const int k)
{
    int left = 0;
    int right = 0;
    // If less than k distinct characters, move right
    // If more than k distinct characters, move left
    int maxLength = 0;
    vector<int> counts(26, 0);
    
    auto getCount = [&counts](int left, int right)
    {
        int result = 0;
        for (int val : counts)
        {
            if (val > 0)
                 result++;
        }
        return result;
    };
        
    while (right < s.size() && getCount(left, right) < k)
    {
        if (getCount(left, right) < k)
        {
            counts[s[right]-'a']++;
            right++;
        }
    }

    if (getCount(left, right) < k)
        return -1;

    right--;

    //"aabbcc"
    while (right < s.size())
    {
        int currCount = getCount(left, right);
        if (currCount < k)
        {
            right++;
            if (right < s.size())
                counts[s[right]-'a']++;
        }
        else if (currCount > k)
        {
            counts[s[left] -'a']--;
            left++;
        }
        else
        {
            maxLength = max(right - left + 1, maxLength);
            right++;
            if (right < s.size())
                counts[s[right]-'a']++;
        }
    }
    return maxLength;
}

int main()
{
    assert(longestWithK("aabbcc", 1) == 2);
    assert(longestWithK("aabbcc", 2) == 4);
    assert(longestWithK("aabbcc", 3) == 6);
    assert(longestWithK("aaabbb",  3) == -1);
    assert(longestWithK("aabacbebebe", 3) == 7);
}