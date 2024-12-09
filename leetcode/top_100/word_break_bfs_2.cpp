#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

bool wordBreak(string s, vector<string>& wordDict) {
	// BFS - use a queue
	// Initial condition - full word
	// During examining of each word from the queue, you try to break down the word into 2 segments (dictionary + remaining)
	// Try to segment a word until it is empty, at which point,  we can return true
	if (s.empty()) {
		return true;
	}
	unordered_set<string> wordDictLookup(wordDict.begin(), wordDict.end());
	queue<string> todo;
	todo.push(s);
	unordered_set<string> visited;
	while (!todo.empty()) {
		const int queueLen = todo.size();
		for (int i = 0 ; i < queueLen; i++) {
			auto current = todo.front();
			todo.pop();
			if (current.empty()) {
				return true;
			}
			visited.insert(current);
			for (int j = 0; j < current.size(); j++) {
				if (wordDictLookup.find(current.substr(0, j + 1)) != wordDictLookup.end()) {
					auto remaining = current.substr(j+1);
					if (visited.find(remaining) == visited.end()) {
						todo.push(current.substr(j + 1));
					}
				}
			}
		}
	}
	return false;

}

int main() {
	std::string s = "leetcode";
	vector<string> dict = {"leet", "code"};
	assert(wordBreak(s, dict));

	s = "applepenapple";
	dict = {"apple", "pen"};
	assert(wordBreak(s, dict));

	s = "catsandog";
	dict = {"cats", "dog", "sand", "and", "cat"};
	assert(!wordBreak(s, dict));

}