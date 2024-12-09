#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;



bool dfs(string s,  int curr, const unordered_set<string>& dict, unordered_set<int>& visited) {
	if (curr == s.size()) {
		return true;
	}

	if (visited.find(curr) != visited.end()) {
		return false;
	}
	visited.insert(curr);
	for (int i = curr ; i < s.size(); i++) {
		auto str = s.substr(curr, i - curr + 1);
		if (dict.find(str) != dict.end()) {
			if (dfs(s, i + 1, dict, visited)) {
				return true;
			}
		}
	}
	return false;
}
bool wordBreak(string s, vector<string>& wordDict) {
	// Convert wordDict -> hash set (unordered_set)
	// do a DFS , where you maintain current position
	// at each level go down further if you match a dictionary word
	// otherwise keep looking down the current path
	unordered_set<int> visited;
	unordered_set<string> dictionary(wordDict.begin(), wordDict.end());
	return dfs(s, 0, dictionary, visited);
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