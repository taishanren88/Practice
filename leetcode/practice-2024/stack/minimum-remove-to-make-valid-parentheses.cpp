#include <iostream>
#include <stack>
using namespace std;

 string minRemoveToMakeValid(string s) {
        // Iterate over the string
 		// IF we encounter '(' , push the index of the characer to stack
 		// If we encounter ')', 
 		// 	1. check the string[stack_top_index] , and if '(', pop off
 		//  2. Else , push to stack
 		// End, itrate over stack positions -- that's evrything we need to remove
 		stack<int> incomplete;
 		for (int i = 0; i < s.size(); i++) {
 			if (s[i] == '(') {
 				incomplete.push(i);
 			} else if (s[i] == ')') { 
 				if (!incomplete.empty() && s[incomplete.top()] == '(') {
 					incomplete.pop();
 				} else {
 					incomplete.push(i);
 				}
 			}
 		}
 		// clean up 
 		for (int i = s.size() - 1; i >=0 ; i-- ){
 			if (!incomplete.empty() && incomplete.top() == i) {
 				s[i] = '#';
 				incomplete.pop();
 			}
 		}
 		s.erase(std::remove(s.begin(), s.end(), '#'), s.end());
 		return s;
    }

int main() {
	cout << minRemoveToMakeValid("lee(t(c)o)de)") << endl;

}