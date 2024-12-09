#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int longestValidParentheses(string s) {
  // create a stack containing incomplete parentheses positions
  // If we encounter a ')' and top of stack is a '(', pop it off
  // compute the distance to the last incomplete parentheses (the one
  // underneath) from current position, -1 if below is empty

  stack<int> incomplete;
  int maxLen = 0;
  auto compute = [&](int current) {
    auto currChar = s[current];
    if (!incomplete.empty() && s[incomplete.top()] == '(') {
      incomplete.pop();
      maxLen =
          max(maxLen, current - (incomplete.empty() ? -1 : incomplete.top()));
    } else {
      incomplete.push(current);
    }
  };

  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(') {
      incomplete.push(i);
    } else {
      compute(i);
    }
  }
  return maxLen;
}

int main() {
  cout << longestValidParentheses("(()") << endl;
  cout << longestValidParentheses(")()())") << endl;
    cout << longestValidParentheses("") << endl;

}