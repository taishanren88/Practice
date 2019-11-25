#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

string decodeString(string s) {
    // Create two separate stacks, one for numbers and one for strings
    // If we hit a number, add the number in, and add empty string because we will start a new sequence
    // If we hit a letter, append letter-stack-top with the letter
    // If we hit a ']', apply transformation using number onto the stack top
    // Put transformation back on stack by appending it to the previous item
    // Return the result
    stack<int> counts;
    stack<string> toprocess;
    toprocess.push("");
    string result;
    for (int i = 0; i < s.size(); i++) {
        string count;
        while (isdigit(s[i])) {
            count += s[i];
            i++;
        }
        if (!count.empty()) {
            counts.push(stoi(count));
            toprocess.push("");
        } else if (s[i] == ']') {
            auto num = counts.top();
            counts.pop();
            string transformed;
            for (int i = 0; i < num; i++) {
                transformed += toprocess.top();
            }
            
            toprocess.pop();
            if (toprocess.empty()) {
                toprocess.push(transformed);
            } else {
                toprocess.top() += transformed;
            }
        }
        else {
            toprocess.top() += s[i];
        }
    }
    
    if (!toprocess.empty()) {
        result += toprocess.top();
    }
    return result;
}

int main() {
    assert(decodeString("3[a]2[bc]") == "aaabcbc");
    assert(decodeString("3[a2[c]]") == "accaccacc");
    assert(decodeString("2[abc]3[cd]ef") == "abcabccdcdcdef");
    assert(decodeString("leetcode") == "leetcode");
}
