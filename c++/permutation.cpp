 /*Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.
Example 1:

Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False */


#include <iostream>
#include <string>
#include <cassert> 
#include <vector>
using namespace std;

bool containsPermutation(string s1, string s2)
{
        vector<int> permutation(128, 0);
        int permLength = 0;
        for (char c: s1)
        {
            permutation[c]++;
            permLength++;   
        }

        vector<int> currentWindow(128,0);
        int currentSize = 0;
        auto checkValid = [&currentWindow, &permutation]()
        {
            for (int i = 0; i < 128; i++)
            {
                if (currentWindow[i] != permutation[i]) return false;
            }
            return true;
        };
        for (int i = 0; i < s2.size(); i++)
        {
             if (i >= permLength)
            {
                if (permutation[s2[i-permLength]])
                    currentWindow[s2[i-permLength]]--;
            }
            cout << s2[i] << currentWindow[s2[i]] << ":" << permutation[s2[i]] <<endl;
            if (permutation[s2[i]] )
            {
                currentWindow[s2[i]]++;
                if (checkValid()) return true;
            }
        }
        return false;
}

int main()
{
    assert(containsPermutation("ab", "eidbaooo") == true);
    assert(containsPermutation("ab",  "eidboaoo") == false);
    assert(containsPermutation("a",  "ab") == true);
    assert(containsPermutation("hello" ,"ooolleoooleh") == false);
    assert(containsPermutation("adc", "dcda") == true);
}
