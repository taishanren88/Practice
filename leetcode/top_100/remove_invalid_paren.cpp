#include <iostream>
#include <string>
#include <vector>
#include <cassert>
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

bool isValidParen(const string& str)
{
	int leftParenToRemove = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			leftParenToRemove++;
		else if (str[i] == ')')
		{
			if (leftParenToRemove == 0)
				return false;
			leftParenToRemove--;
		}
	}
	return leftParenToRemove == 0;
}
void generateString(const string& original, int pos, int leftParenToRemove, int rightParenToRemove, int leftParenOpen,
					string curr,unordered_set<string>& results)
{
	if (leftParenToRemove < 0 || rightParenToRemove < 0 || leftParenOpen < 0) /* Optimization */
		return;

	if (pos == original.size())
	{
		if (leftParenToRemove == 0 && rightParenToRemove == 0 && leftParenOpen == 0)
		{
			results.insert(curr);
		}

		return;
	}

	if (original[pos] == '(')
	{
		generateString(original, pos + 1, leftParenToRemove, rightParenToRemove, leftParenOpen + 1, curr + original[pos],results);
		generateString(original, pos + 1, leftParenToRemove -1, rightParenToRemove, leftParenOpen, curr, results);

	}
	else if (original[pos] == ')')
	{
		generateString(original, pos + 1, leftParenToRemove, rightParenToRemove, leftParenOpen -1, curr + original[pos], results);
		generateString(original, pos + 1, leftParenToRemove, rightParenToRemove - 1, leftParenOpen, curr,  results);
	}
	else
		generateString(original, pos +1, leftParenToRemove, rightParenToRemove, leftParenOpen, curr + original[pos], results);

	if (original[pos] == '(')
		leftParenToRemove--;
	else if (original[pos] == ')')
		rightParenToRemove--;
}

vector<string> removeInvalidParentheses(string s) {
    // Using recursion, brute force this.
    // 1. Get minimum of left/right parentheses we know we have to remove
    // 2. DFS: Remove the current parentheses
    // 3. OR keep it
    // At the end , check if th string is valid
    // Keep track of minimum length, current string, and final result
    int min = INT_MAX;
    unordered_set<string> results;
    int leftParenToRemoveCount = 0; // to remove from original string
    int rightParenToRemoveCount = 0;
    int leftParenOpen = 0; // to remove from 'current' string
    for (char c : s)
    {
    	if (c == '(')
    		leftParenToRemoveCount++;
    	else if (c == ')') {
    		if (leftParenToRemoveCount == 0)
    			rightParenToRemoveCount++;
    		else
    			leftParenToRemoveCount--;
    	}

    }

    generateString(s, 0,  leftParenToRemoveCount, rightParenToRemoveCount, leftParenOpen, "", results);
    return vector<string>(results.begin(), results.end());
}

int main() {
	auto print =[](const vector<string>& input) {
		std::ostream_iterator<string> out_it (std::cout, ", ");
  	 	std::copy (input.begin(), input.end(), out_it );
  	 	cout << endl;
	};
	assert(isValidParen("()()"));
	assert(!isValidParen("()())"));
	assert(!isValidParen("(()()"));
	auto result = removeInvalidParentheses("()())()");
	print(result);
	result = removeInvalidParentheses("(a)())()");
	print(result);
	result = removeInvalidParentheses(")(");
	print(result);
	cout << result.size() << endl;
	cout << endl;

}