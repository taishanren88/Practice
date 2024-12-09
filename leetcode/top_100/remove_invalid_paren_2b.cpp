#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
using namespace std;

bool isValid(std::string s) {
	int openParen = 0;
	for (char c : s) {
		if (c == '(') {
			openParen++;
		} else if (c == ')') {
			if (openParen > 0) {
				openParen--;
			} else {
				return false;
			}
		}
	}
	return openParen == 0;
}
vector<string> removeInvalidParentheses(string s) {
	// Do a BFS , starting with existing string as the first path
	// At each point, pop an element off the queue, and check if it's valid, if so we are done.
	// How to determine if a string is valid ? Loop over it and check # of open parentheses are closed

	queue<string> todo;
	todo.push(s);
	unordered_set<string> results;
	unordered_set<string> visited;
	while (!todo.empty()) {
		auto currentLen = todo.size();
		for (int i = 0; i < currentLen; i++) {
			auto current = todo.front();
			todo.pop();
			if (isValid(current)) {
				results.insert(current);
			}
			for (int j = 0 ; j < current.size(); j++) {
				auto possibleStr = current.substr(0, j) + current.substr(j + 1);
				if (visited.find(possibleStr) == visited.end()) {
					visited.insert(possibleStr);
					todo.push(possibleStr);
				}

			}
		}
		if (!results.empty()) {
			break;
		}
	}
	return vector<string>(results.begin(), results.end());
}

int main() {
	assert(isValid("()()()"));
	assert(!isValid("()())()"));
	assert(isValid("(a)()()"));
	assert(!isValid(")("));
	auto print = [] (vector<string> result) {
		for (auto s : result) {
			cout << s << ",";
		}
		cout << endl;
	};
	auto res = removeInvalidParentheses("()())()");

	print(res);
	res = removeInvalidParentheses("(a)())()");
	print(res);
	res = removeInvalidParentheses(")(");
	print(res);

}