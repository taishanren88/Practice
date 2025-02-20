#include <iostream>
#include <string>
#include <stack>
using namespace std;
string minRemoveToMakeValid(string s) {
    // Iterate over string
	// If it's a '(', push its positoin to stack
	// If ts a ')' , pop off the top of the stack if there's existing '('
	// 
	// // at the end convert all positions at the stack to something special 
	stack<int> invalidPositions;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			invalidPositions.push(i);
		} else if (s[i] == ')') {
			if (!invalidPositions.empty() 
				&& s[invalidPositions.top()] == '(') {
				invalidPositions.pop();
			} else {
				invalidPositions.push(i);
			}
		}
	}
	while (!invalidPositions.empty()) {
		s[invalidPositions.top()] = '#';
		invalidPositions.pop();
	}
	s.erase(std::remove(s.begin(), s.end(), '#'), s.end());
	return s;
}

int main() {
	cout << minRemoveToMakeValid("lee(t(c)o)de)") << endl;
	
}