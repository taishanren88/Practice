#include <iostream>
#include <cassert>
using namespace std;

    // if you see a digit , pass in current index + 2
    // if it's not a digit keep appending the character 
    // return the string , the next index to be looked at 

    bool isLetter(char c)
    {
        c = tolower(c);
        return c >= 'a' && c <= 'z'; 
    }
    tuple<string,int> helper(string s, int start, int end)
    {
        int i = start;
        string current;
        string digits;
        while (i < end && s[i] != ']')
        {
            if (isLetter(s[i]))
            {
                current += s[i];
                i++;
            }
            else if (isdigit(s[i]))// it's a digit
            {
                digits += s[i];
                i++;
            }
            else  // '['
            {
                auto tup = helper(s, i + 1, end);
                int count = stoi(digits);
                cout << count;
                i = get<1>(tup) + 1;
                for (int j = 0 ; j < count; j++)
                {
                    current += get<0>(tup);
                }
                digits="";
            }
        }
        return make_tuple(current, i);
    }
    string decodeString(string s) {
        auto ret= helper(s, 0, s.size());   
        return get<0>(ret);
    }
    
int main()
{
    string s = decodeString("3[a]2[bc]");
    assert( s== "aaabcbc");
    assert(decodeString("3[a2[c]]") == "accaccacc");
    assert(decodeString("2[abc]3[cd]ef") == "abcabccdcdcdef");
    cout << decodeString("100[leetcode]");
    
}
