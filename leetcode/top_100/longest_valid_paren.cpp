#include <iostream>
#include <string>
#include <stack>
using namespace std;

 int longestValidParentheses(string s) {
        // We want to find all of the invalid positions
        // If we encounter a ')', when a stack already has a '(', pop and compute the distance, to the stack top, since the stack top at that moment will have the last invalid position.
        
        stack<int> positions;
        int longest = 0;
        for (int i = 0 ;i < s.size() ;i++){
        	cout << i << endl;
            if (s[i] == '(') {
                positions.push(i);
            } else if (s[i] == ')') {
                if (!positions.empty() &&
                	s[positions.top()] == '(') {
                    positions.pop();
                    int left =  positions.empty() ? -1 : positions.top();
                    longest = max(longest, i - left);
                }
                else {
                    positions.push(i);
                }
            }
        }
        return longest;
    }

    int main() {
    	assert(longestValidParentheses("(()")  == 2);
    	 assert(longestValidParentheses(")()())") == 4);
    	assert(longestValidParentheses("()()") == 4);
    }