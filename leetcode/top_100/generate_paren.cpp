#include <iostream>
#include <vector>
#include <string>
using namespace std;

void helper(string curr, int open, int closed, int n, vector<string>& results) {
	if (closed == n) {
		results.push_back(curr);
	} else {
		if (open < n) {
			helper(curr + '(', open + 1, closed, n, results);
		}
		if (closed < open ) {
			curr += ')';
			helper(curr, open , closed +1, n, results);
		}
	}
}
vector<string> generateParenthesis(int n) {
    // Recursive function, keep track of how many open parentheses we have
    // If closed and open == n , done
    // If number of closed is < open , close it
	// If open < n , keep opening
	vector<string> results;
	helper("", 0, 0, n, results);
	return results;
}
int main() {

	vector<string> results = generateParenthesis(3);
	for (auto res : results ) {
		cout << res << endl;
	}
}