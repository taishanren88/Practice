#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


unordered_map<int, vector<char>> mapping = {{2, {'a', 'b','c'}}, {3, {'d', 'e','f'}}, {4, {'g', 'h','i'}}, 
											{5, {'j', 'k', 'l'}}, {6, {'m', 'n', 'o'}},{7, {'p', 'q', 'r','s'}},
											{8, {'t', 'u', 'v'}}, {9, {'w', 'x','y','z'}}};

void helper(string digits, int pos, string curr, vector<string> & results) {

	if (pos == digits.size()) {
		results.push_back(curr);
	}

	const auto currDigit = digits[pos] - '0';
	for (char c :mapping[currDigit] ) {
		helper(digits, pos + 1, curr + c , results);
	}
}

vector<string> letterCombinations(string digits) {
    // For each digit, find all posibilities (use map to find)
    // If reach end add result to vector
    if (digits.empty()) {
    	return {};
    }
    vector<string> results;
	helper(digits, 0, "", results);
	return results;
}

int main() {
	auto res = letterCombinations("23");
	for (auto str : res ) {
		cout << str << ",";
	}
}