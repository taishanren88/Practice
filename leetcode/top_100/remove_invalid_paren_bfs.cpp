#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

/**
Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]
*/

vector<string> removeInvalidParentheses(string s) {
    // Do a BFS where we remove one parentheses at a time
    // At each level, we iterate through every string
    // For each string if it's a '(' or ')' , we remove one parentheses from the string at a time
    // We stop at the current level if we found a valid string
    queue<string> toprocess;
    toprocess.push(s);
    
    auto isValid =[](const string& target) {
        int openParen = 0;
        for (char c : target ) {
            if (c == '(')
                openParen++;
            else if (c == ')') {
                if (openParen == 0)
                    return false;
                openParen--;
            }
        }
        return openParen == 0;
    };

    bool remaining = true;
    unordered_set<string> results;
    unordered_set<string> visited;
    while (!toprocess.empty()) {
        int len = toprocess.size();
        for (int i = 0; i < len; i++) {
            auto curr = toprocess.front();
            toprocess.pop();
            
            // handle validity
            if (isValid(curr)) {
                 results.insert(curr);
                remaining = false;
            }
            
            if (remaining) {
                for (int i = 0; i < curr.size(); i++) {
                    if (curr[i] == '(' || curr[i] == ')') {
                    	auto next = curr.substr(0, i) + curr.substr(i+1);
                    	if (visited.find(next) == visited.end()) {
                        	toprocess.push(next);
                        	visited.insert(next);
                    	}
                    }
                }
            }
        }
    }
    return vector<string>(results.begin(), results.end());
}
int main() {
	auto print =[](const vector<string>& input) {
		std::ostream_iterator<string> out_it (std::cout, ", ");
  	 	std::copy (input.begin(), input.end(), out_it );
  	 	cout << endl;
	};

	auto result = removeInvalidParentheses("()())()");
	print(result);
	result = removeInvalidParentheses("(a)())()");
	print(result);
	result = removeInvalidParentheses(")(");
	print(result);
	result = removeInvalidParentheses("((()((s((((()");
	print(result);
	cout << result.size() << endl;
	cout << endl;

}