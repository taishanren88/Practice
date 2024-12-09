#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

using Path = std::vector<string>;
vector<Path> findLaddersHelper(string beginWord, string endWord, unordered_set<string>& wordDict) {
    // maintain a queue of paths to iterat over. Paths are a vector of a strings
    // For each loop, iterate over all paths, find next words to the last entry of the path. 
    // If un-visited, add to the path
    // Add these words back to "visited" section and ensure we don't iterate over them again
    // We know we are done, when we encounter the last element to the "visited " section"
    queue<Path> paths;
    vector<Path> results;
    Path p = {beginWord};
    paths.push(p);
    unordered_set<string> alreadyConsidered;
    while (!paths.empty()) {
    	for (auto str : alreadyConsidered ) {
    		if (str == endWord) {
    			return results;
    		}
    		wordDict.erase(str);
    	}
    	alreadyConsidered.clear();
    	int numPaths = paths.size();
    	for (int i = 0; i < numPaths; i++) {
    		auto path = paths.front();
    		paths.pop();
    		auto lastWord = path.back();
    		// Find all possible next words
    		for (int k = 0; k < lastWord.size(); k++) {
    			char original = lastWord[k];
	    		for (int j = 0; j < 26 ; j++) {
	    			char c = 'a' + j ;
	    			if (c != original ) {
	    				lastWord[k] = c;
	    				// found in dictionary
	    				if (wordDict.find(lastWord) != wordDict.end()) {
	    					Path nextPath = path;
	    					nextPath.push_back(lastWord);
	    					paths.push(nextPath);
	    					alreadyConsidered.insert(lastWord);
	    					if (lastWord == endWord) {
	    						results.push_back(nextPath);
	    					}
	    				}
	    				lastWord[k] = original;
	    			}
	    		}
    		}
    	}
    }
    return results;
}
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    // maintain a list of paths to iterat over. Paths are a vector of a strings
    // For each loop, iterate over all paths, find next words to the last entry of the path. 
    // If un-visited, add to the path
    // Add these words back to "visited" section and ensure we don't iterate over them again
    // We know we are done, when we encounter the last element to the "visited " section"
    unordered_set<string> wordDict(wordList.begin(), wordList.end());
  	return findLaddersHelper(beginWord, endWord, wordDict);
}

int main() {
	auto print =[] (vector<string>& path) {
	    for (auto s : path) {
	        cout << s << ",";
	    }
	    cout << endl;
	};

	vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    auto result1 = findLadders("hit", "cog", wordList);
    for (auto result : result1) {
        print(result);
        cout << endl;
    }

    vector<string> wordList2 = {"a", "b", "c"};
    auto result22 = findLadders("a", "c", wordList2);
    for (auto result : result22) {
        print(result);
        cout << endl;
    }
   vector<string> wordList3 = {"hot", "dog", "dot"};
    auto result23 = findLadders("hot", "dog", wordList3);
    for (auto result : result23) {
        print(result);
        cout << endl;
    }
}