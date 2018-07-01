  #include <iostream>
#include <cassert>
using namespace std;
   bool wrapper(string s, int start, int end, int leftParen)
    {
        cout << "start " << start << "left paren " << leftParen << endl;

        for (int i = start; i < end; i++)
        {
            if (s[i] == '(') // add a count of left parentheses
            {
                leftParen++;
            }
            else if (s[i] == ')')
            {
                leftParen--;
                if (leftParen < 0) // can't ahve more ')' than '('
                    return false;
            }
            else if (s[i] == '*')
            {
                // 3 possibilities
                // 1. Left Parentheses
                // 2. Right parentehese
                // 3. continue
                
                if ( (leftParen >= 1 && wrapper(s, i + 1, end, leftParen -1) )
                      || wrapper(s, i + 1, end, leftParen + 1))
                    return true;
                // else continue as if null string
            }
        }
        return leftParen == 0;
    }
    bool checkValidString(string s) {
        return wrapper(s, 0, s.size(), 0);
    }
    
    int main()
    {
        assert(checkValidString("(*()"));
    }
