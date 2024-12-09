#include <iostream>
#include <stack>
using namespace std;

int longestValidParentheses(string s) {
    // Maintain a stack of all the 'invalid' parenthese indices
    // If encounter '(', push to the top of the stack
    // Each time we encounter a ')' and the top of the stack is not '(', it's invalid,
    // everything in betweeen is valid
	stack<int> invalid;
	int longestLen = 0;
	auto compute =[&](int index){
			if (invalid.empty()) {
				longestLen = max(longestLen, index);
				invalid.push(index);
			} else {
				if (s[invalid.top()] == '(') {
					invalid.pop();
				} else {
					longestLen = max(longestLen , index - invalid.top() - 1);
					invalid.push(')');
				}
			}
	};
	for (int i = 0 ; i < s.size(); i++) {
		if (s[i] == '(') {
			invalid.push(i);
		} else {
			compute(i);
		}
	}
	longestLen = max(longestLen,(int) s.size() -(invalid.empty() ? 0 : invalid.top() +1));
    return longestLen;
}

int main() {
	assert(longestValidParentheses("(()")  == 2);
    assert(longestValidParentheses("()()") == 4);
    assert(longestValidParentheses(")()())") == 4);
}