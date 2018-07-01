#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

    vector<int> findAnagrams(string s, string p) {
        vector<int> results;
        unordered_map<char, int> charToCount;
        int left = 0;
        int right = 0;
        int pCount = p.size();
        for (int i = 0; i < p.size(); i++)
        {
            if (charToCount.find(p[i]) != charToCount.end())
                charToCount[p[i]]++;
            else
                charToCount[p[i]] = 1;
        }
        while (right < s.size())
        {
            // example s: "abab" p: "ab"
            if (charToCount.find(s[right]) != charToCount.end())
            {
                if (charToCount[s[right]] >= 1)
                {
                    pCount--;

                }
                charToCount[s[right]]--;
            }

            cout << s[right] << ", still has" << charToCount[s[right]] << " and a total ";
            cout << "Count " << pCount << endl;

            right++;
            if (pCount == 0)
                results.push_back(left);

            if (right - left == p.size())
            {
                if (charToCount.find(s[left]) != charToCount.end())
                {
                    if (charToCount[s[left]] >= 0)
                    {
                        pCount++;
                    }
                    charToCount[s[left]]++;
                }
                left++;
            }
        }
        return results;
    }
    
    int main()
    {
        auto res = findAnagrams("abccba", "abc");
        cout <<endl;
        for (int s : res)
        {
            cout << s <<endl;
        }
        
    }
