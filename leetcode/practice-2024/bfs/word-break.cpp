#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

bool wordBreak(string s, vector<string>& wordDict) {
	// Do a BFS where we maintain a queue of words we need to visit
	// For each word from the queue, break the word at all possible points of its length
	// Check if the current word exists in the dictionary, if so push it to queue
	// // Check if the remaining word exists in the dictionary , if so we are done

	queue<string> todo;
	unordered_set<string> dictionary(wordDict.begin(), wordDict.end());
	unordered_set<string> visited;
	todo.push(s);
	if (dictionary.find(s) != dictionary.end()) {
		return true;
	}
	while (!todo.empty()) {
		auto currWord = todo.front();
		todo.pop();
		if (visited.find(currWord) != visited.end()) {
			continue;
		}
		visited.insert(currWord);
		for (int j = 0; j < currWord.size(); j++) {
			auto start = currWord.substr(0, j + 1);
			auto end = currWord.substr(j + 1);
			if (dictionary.find(start) != dictionary.end()) {
				if (dictionary.find(end) != dictionary.end()) {
					return true;
				}
				todo.push(end);
				// cout << "push " << endl;
			}
		}
	}
	return false;
}
int main() {
	// vector<string>  wordDict1 = {"leet", "code"};
	// cout << wordBreak ("leetcode", wordDict1) << endl;


vector<string>  wordDict2 = {"apple", "pen"};
	cout << wordBreak ("applepenapple", wordDict2) << endl;


vector<string>  wordDict3 = {"cats", "dog", "sand", "and", "cat"};
	cout << wordBreak ("catsandog", wordDict3) << endl;

vector<string>  wordDict4 = {"a"};
	cout << wordBreak("a", wordDict4) << endl;
}