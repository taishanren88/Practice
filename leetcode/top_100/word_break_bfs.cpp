#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

bool wordBreak(string s, vector<string>& wordDict) {
	// Convert wordDict -> hash set (unordered_set)
	// do BFS DFS , where you maintain start position , and current position
	// Maintain a visited array where you rememmber all of the positions you've visited already
	// Iterate : Over start positions, for each start position, expand from that index. 
	// if we find a word we know, append the rest to the queue. If we reach the end we are done
	unordered_set<int> visited;
	unordered_set<string> dict (wordDict.begin(), wordDict.end());
	queue<int> todo;
	todo.push(0);
	while (!todo.empty()) {
		int len = todo.size();
		for (int i = 0; i < len ; i++) {
			auto current = todo.front();
			todo.pop();
			if (current == s.size()) {
				return true;
			}
			if (visited.find(current) != visited.end()) {
				continue;
			}
			visited.insert(current);
			for (int i = current;  i < s.size(); i++) {
				auto target = s.substr(current, i - current + 1);
				if (dict.find(target) != dict.end()) {
					todo.push(i +1);
				}
			}
		}
	}
	return false;
}


int main() {
	vector<string> dict = {"leet", "code"};

	assert(wordBreak("leetcode", dict));
	 dict = {"apple", "pen"};

	assert(wordBreak("applepenapple", dict));

	dict = {"cats", "dog", "sand", "and", "cat"};

	assert(!wordBreak("catsandog", dict));
 	dict = {"aaaa", "aaa"};

	 assert(wordBreak("aaaaaaa", dict));

	 dict = {"aa", "a"};
	 assert(wordBreak("aaaaaa", dict));
}