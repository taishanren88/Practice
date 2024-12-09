#include <iostream>
#include <stack>
using namespace std;

int longestValidParentheses(string s) {
	// Create a stack of positions, representing unclosed values
	// Iterate over s
	// if s[i] == ')', see if to pof stack is '(', if so pop
	// The max is the distance from current position to the stack top or -1
	// if s[i] == '(', push to stack
	stack<int> incomplete;
	int runningMax = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			incomplete.push(i);
		} else {
			if (incomplete.empty()) {
				incomplete.push(i);
			}  else if (s[incomplete.top()] == '('){
				incomplete.pop();
				auto currentMax = i - (incomplete.empty() ? -1 : incomplete.top());
				runningMax = max(runningMax, currentMax);
			} else {
				incomplete.push(i);
			}
		}
	}
	return runningMax;
}

int main() {
	cout << longestValidParentheses("(()") << endl;
		cout << longestValidParentheses(")()())") << endl;
		cout << longestValidParentheses(")()())()()(") << endl;

}