#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

    void generatePermutate(string s, int curr, int end, vector<string>& perms)
    {
          if (curr == end)
             perms.push_back(s);
           else
           {
               // fix each character, and then fix the rest
               for (int i = curr; i <= end; i++)
               {
                  swap(s[i], s[curr]); // fix the current character
                  generatePermutate(s, curr + 1, end, perms);
                  swap(s[i], s[curr]); //backtrack
               }
           }
    }
    bool checkInclusion(string s1, string s2) {
        vector<string> perms;
         generatePermutate(s1, 0, s1.size() - 1,  perms);
        for (string s : perms)
        {
            // cout << s << endl;
            if (s2.find(s) != string::npos)
                return true;
        }
        return false;
    }
    
int main()
{
    assert(checkInclusion("adc", "dcda"));
    assert(checkInclusion("ab", "eidbaooo"));
    assert(checkInclusion("abc", "bbbca"));
}
