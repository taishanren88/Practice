#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generateParenthesisHelper(string s, int leftParen, 
int closeParen, int n, vector<string>& results) {
if (closeParen == n) {
	results.push_back(s);
} else {
	if (leftParen < n) {
		generateParenthesisHelper(s + '(', leftParen + 1, closeParen, n, results);
	}
if (closeParen < leftParen) {
		// cout << "left:" << to_string(leftParen) << "," << to_string(closeParen) << endl;
		generateParenthesisHelper(s + ')', leftParen, closeParen + 1,n,  results);
	}
	}
}
vector<string> generateParenthesis(int n) {
    // Create a helper function. 
	// At each point keep track of left open parentheses, and the number remaining ("n")
	// At each point, you can close the running string if there are left parentheses > 0
	// If we reach a point where left parentheses == 0 , then just return and append to the result
    vector<string> results;
    generateParenthesisHelper("", 0, 0, n, results);
    return results;
 }

int main() {
	auto res =  generateParenthesis(1);
	for (auto s : res ) {
		cout << s << ",";
	}
	cout << endl;

	 res =  generateParenthesis(3);
	for (auto s : res ) {
		cout << s << ",";
	}
	cout << endl;

}