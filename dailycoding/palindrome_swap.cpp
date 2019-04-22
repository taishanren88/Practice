#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

bool isValidPalindromeSwap(const std::string& str)
{

    vector<char> different(4, '0');
    int differentCount = 0;
    int i = 0;
    int j = str.size() - 1;
    while (i <= j)
    {
        if (str[i] != str[j])
        {
             if (differentCount == 2)
                return false;
            if (differentCount == 0)
            {
                different[0] = str[i];
                different[1] = str[j];
            }
            else
            {
                different[2] = str[i];
                different[3] = str[j];
            }
            differentCount++;
        }
        i++;
        j--;
    }

    // swap count == 0 -> Always ture;
    if (differentCount == 0) 
        return true;

    if (differentCount == 1)
    {
        // Must be odd and one 'different' character must be same as middle
        // Even case: Willl never work (Ex " abbd)
        // Odd case: 1. abd (wont work), 2. aad (works - same as middle character)
        int mid = str.size() / 2;
        return str.size() %2 == 1 && (different[0] == str[mid] || different[1] == str[mid]);
    }

    return ( (different[0] == different[2] && different[1] == different[3])
              || (different[1] == different[2] && different[0] == different[3]));
}
int main()
{
    assert(isValidPalindromeSwap("bbg"));
    assert(!isValidPalindromeSwap("gbd"));

     assert(isValidPalindromeSwap("bdababd"));
     assert(isValidPalindromeSwap("bdaabd"));
     assert(!isValidPalindromeSwap("gcagac"));
}