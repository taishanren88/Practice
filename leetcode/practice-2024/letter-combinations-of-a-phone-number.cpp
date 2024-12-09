#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

vector<string> letterCombinations(string digits) {
    // iterate over the string
    // build a queue of remaining strings to processs
    // maintain the current index of the string
    // pop from the queue and find next possible list of combinations
    unordered_map<char, string> mapping {
    	{'2', "abc"}, {'3', "def"}, {'4', "ghi"},
    	  {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
    	  {'8', "tuv"}, {'9', "wxyz"}
    };
    int pos = 0;
    queue<string> todo;
    todo.push("");
    for (int i = 0; i < digits.size(); i++) {
    	auto len = todo.size();
    	for (int j = 0; j < len ; j++) {
    		auto front = todo.front();
    		todo.pop();
    		for (char c :  mapping[digits[i]]) {
    			todo.push(front + c );
    		}
    	}
    }
    vector<string> results;
    while (!todo.empty()) {
    	auto front = todo.front();
    	todo.pop();
    	if (!front.empty()) {
    		results.push_back(front);
    	}
    }
    return results;
}

int main() {
	auto res = letterCombinations("23");
	for (auto str : res ) {
		cout << str << " ,";
	}
	cout << endl;

	 res = letterCombinations("");
	for (auto str : res ) {
		cout << str << " ,";
	}
	cout << endl;

	 res = letterCombinations("2");
	for (auto str : res ) {
		cout << str << " ,";
	}
	cout << endl;
}