#include <iostream>
#include <cassert>
#include <unordered_map>
using namespace std;

int romanToInt(string s) {
    // Go through each number
    // If it's a special case, the current character s[i] < s[i+1]
    // In which case subtract the current value
    // 'IV' -> -1 + 5
    // 'IX' -> -1 + 10
    int result = 0;
     unordered_map<char, int> mapping = { 
                                   { 'I' , 1 },
                                   { 'V' , 5 },
                                   { 'X' , 10 },
                                   { 'L' , 50 },
                                   { 'C' , 100 },
                                   { 'D' , 500 },
                                   { 'M' , 1000 } };
                                   

    for (int i = 0; i < s.size(); i++)
    {
        if ( (i < (s.size() - 1 )) 
            && mapping[s[i]] < mapping[s[i+1]])
            result -= mapping[s[i]];
        else

            result += mapping[s[i]];
    }
    return result;
}

int main () {
    assert(romanToInt("III") == 3);
    assert(romanToInt("IV") == 4);
    assert(romanToInt("IX") == 9);
    assert(romanToInt("LVIII") == 58);
    assert(romanToInt("MCMXCIV") == 1994);
    assert(romanToInt("MCDLXXVI") == 1476);
}