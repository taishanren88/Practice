#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;


unordered_map<int, vector<char>> mapping = {{2, {'a', 'b','c'}}, {3, {'d', 'e','f'}}, {4, {'g', 'h','i'}}, 
											{5, {'j', 'k', 'l'}}, {6, {'m', 'n', 'o'}},{7, {'p', 'q', 'r','s'}},
											{8, {'t', 'u', 'v'}}, {9, {'w', 'x','y','z'}}};


vector<string> letterCombinations(string digits) {
    // Iterate: For each digit, find all posibilities (use map to find)
    // Maintain a queue to store past results
    // Pop off all previous entries and then append current digit to them and push back
    if (digits.empty()) {
    	return {};
    }
    queue<string> todo;
    todo.push("");
    for (char c : digits ) {
    	int queueLen = todo.size();
    	for (int i = 0; i <  queueLen;  i++) {
	    	auto previous = todo.front();
	    	todo.pop();
	    	auto currentDigit = c - '0';
	    	for (char possible : mapping[currentDigit]) {
	    		todo.push(previous + possible);
	    	}
		}
	}
	vector<string> results;
	while (!todo.empty()) {
		auto front = todo.front();
		todo.pop();
		results.push_back(front);
	}

	return results;
}

int main() {
	auto res = letterCombinations("23");
	for (auto str : res ) {
		cout << str << ",";
	}
}