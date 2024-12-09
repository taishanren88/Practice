#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

vector<string> removeInvalidParentheses(string s) {
    // use a queue to find out all the possibilities
    // pop , and validate. if (valid - add to result)
    // once found , add all remaining on the same level of queue
    // else, find all possibilities by creating different substrings, removing a parentheses at each position

	auto isValid=[](string curr ) {
		int openParen = 0;
		for (int i = 0; i < curr.size(); i++) {
			if (curr[i] == '(') {
				openParen++;
			} else if(curr[i] == ')'){
				openParen--;
				if (openParen < 0) {
					return false;
				}
			}
		}
		return openParen == 0;
	};
	queue<string> unvisited;
	unordered_set<string> considered;
	unvisited.push(s);
	vector<string> results;
	while (!unvisited.empty()) {
		auto curr = unvisited.front();
		unvisited.pop();
		if (isValid(curr)){
			results.push_back(curr);
		} else {
			if (!results.empty()) { // found a valid result, should stop looking beyond this level
				continue;
			}
			for (int i = 0; i < curr.size(); i++) {
				if (curr[i] == '(' || curr[i] == ')') {
					string possible = curr.substr(0, i) + curr.substr(i+1);
					if (considered.find(possible) == considered.end()) {
						unvisited.push(possible);
						considered.insert(possible);
					}
				}
			}
		}
	}
	return results;
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

}