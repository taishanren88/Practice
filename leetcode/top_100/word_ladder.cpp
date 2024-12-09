#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    // Do a BFS traversal
    // At each point , compute the transformations of all the possible 'next' words. If a transformation hasn't been visited, add it to the queue
    // Visit
    // If we reach the end , we are done (take the current cost + 1)
	queue<string> toVisit;
	unordered_set<string> visited;
	unordered_set<string> dict(wordList.begin(), wordList.end());
	toVisit.push(beginWord);
	int minCost = 0;
	while (!toVisit.empty()) {
		int queueLen = toVisit.size();
		minCost++;
		for (int l = 0; l < queueLen; l++) {
			auto front = toVisit.front();
			toVisit.pop();
			// compute the next transformations
			for (int i = 0 ; i < front.size(); i++) {
				char original = front[i];
				for (int j = 0; j < 26; j++) {
					char c = 'a' + j;
					if (c != original) {
						front[i] = c;
						if (dict.find(front) != dict.end()
							&& visited.find(front) == visited.end()) {
							if (endWord == front) {
								return minCost + 1;
							}
							toVisit.push(front);
							visited.insert(front);
						}
					}
				}
				front[i] = original;
			}
		}
	}
	return 0;
}

int main() {
	vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
	cout << ladderLength("hit", "cog", wordList) << endl;
	assert(ladderLength("hit", "cog", wordList) == 5);
	wordList =  {"hot","dot","dog","lot","log"};
	assert(ladderLength("hit", "cog",wordList) == 0);
	wordList = {"a" , "b", "c"};
	assert(ladderLength("a", "c", wordList) == 2);

}