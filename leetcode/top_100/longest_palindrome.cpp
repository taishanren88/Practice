#include <iostream>
#include <string>
using namespace std;

std::string expand(string s, int left, int right) {
    while (left -1 >= 0 && right  + 1 < s.size()
            &&s[left - 1 ] == s[right + 1]) {
        left--;
        right++;
    }
    return s.substr(left, right - left + 1);
}

std::string longestPalindrome(string s) {
    // Loop over the string
    // expand from the left and right around each point
    // compute the maximum length
    std::string result;
    for (int i = 0; i < s.size(); i++){
        auto resultOdd = expand(s, i, i);

        result = resultOdd.size() > result.size() ? resultOdd : result;
        if (i + 1 < s.size() &&
            s[i] == s[i+1]) {
            auto resultEven = expand(s, i, i + 1);
            result = resultEven.size() > result.size() ? resultEven : result;
        }
    }
    return result;
}

int main() {

    assert(longestPalindrome("babad") == "bab");
    assert(longestPalindrome("cbbd") == "bb");

}