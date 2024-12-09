#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

vector<string> getNextSetOfWords(string word, unordered_set<string>& dict) {
	vector<string> result;
	for (int j = 0; j < word.size(); j++) {
		auto original = word[j];
		for (int i = 0; i < 26; i++) {
			char replace = 'a' + i;
			if (replace != original) {
				word[j] = replace;
				if (dict.find(word) != dict.end()) {
					result.push_back(word);
				}
				word[j] = original;
			}
		}

	}
	return result;
}
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {

	// Do a BFS with a vector of paths as each entry
	// Repeat searching until we find the target endWord
	// Start with vector containing the beginWord"
	// At each iteration pop off a path and the last word in the path and get the next transformation sequence
	// Maintain a "visited" set so that we don't revisit the same word twice
	using Path = vector<string>;
	queue<Path> todo;
	Path initialPath = {beginWord};
	todo.push(initialPath);
	unordered_set<string> wordListLookup(wordList.begin(), wordList.end());
	unordered_set<string> visited;
	vector<Path> results;
	while (!todo.empty()) {
		const int queueLen = todo.size();
		unordered_set<string> currentLevelVisited;
		for (int i = 0; i < queueLen; i++) {
			auto currentPath = todo.front();
			todo.pop();
			auto lastWord = currentPath.back();
			if (lastWord == endWord) {
				results.push_back(currentPath);
			}
			auto nextPossibleSetOfWords = getNextSetOfWords(lastWord, wordListLookup);
			for (auto word : nextPossibleSetOfWords) {
				if (visited.find(word) == visited.end()) {
					currentLevelVisited.insert(word);
					auto newPath = currentPath;
					newPath.push_back(word);
					todo.push(newPath);
				}
			}
		}
		if (!results.empty()) {
			break;
		}
		visited.insert(currentLevelVisited.begin(), currentLevelVisited.end());
	}
	return results;
}

int main() {
	unordered_set<string> dict = {"hot", "hat"};
	auto res = getNextSetOfWords("hit", dict);
	assert(res.size() == 2
	       && res[0] == "hat" && res[1] == "hot");

	auto print = [] (vector<vector<string>>& paths) {
		for (auto path : paths) {
			for (auto s : path) {
				cout << s << ",";
			}
			cout << endl;
		}
	};

	vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
	vector<vector<string>> result = findLadders("hit", "cog", wordList );
	print(result);
	vector<string> wordList2 = {"a", "b", "c"};
	auto result2 = findLadders("a", "c", wordList2);
	print(result2);

	vector<string> wordList3 = {"hot", "dog", "dot"};
	auto result3 =   findLadders("hot", "dog", wordList3);
	print(result3);
}