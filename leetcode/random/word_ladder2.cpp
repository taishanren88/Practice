#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

    void dfs(string currentWord, string endWord, int targetLen,
              unordered_map<string, vector<string>>& graph, 
              unordered_map<string, int>& minCost,
              vector<string>& path, vector<vector<string>>& results) {
       
 
        if (currentWord == endWord ) {
        	path.push_back(currentWord);
        	if (path.size() == targetLen)
           		results.push_back(path);
           path.pop_back();
           return;
        }

        path.push_back(currentWord);
        for (const auto neighbor : graph[currentWord]) {
            if ( path.size() + 1 == minCost[neighbor]) {
                dfs(neighbor, endWord, targetLen, graph, minCost, path, results);
            }
        }
        path.pop_back();
 
    }

    int ladderLength (string beginWord, string endWord, vector<string>& wordList, 
    				        unordered_map<string, vector<string>>& oGraph,
    				        unordered_map<string, int>& oDistance
) {
    	queue<string> remaining;
    	remaining.push(beginWord);
    	int count = 0;
    	unordered_set<string> dict (wordList.begin(), wordList.end());
    	unordered_set<string> visited;
    	while (!remaining.empty()) {
    		int level = remaining.size();
    		count ++;
    		for (int i = 0; i < level; i++) {
	    		auto top = remaining.front();
	    		remaining.pop();
	    		if (visited.find(top) != visited.end())
	    			continue;
	    		visited.insert(top);
	    		oDistance[top] = count;

	    		if (top == endWord) {
	    			return count;
	    		}
	    		auto current = top;
	            for (int index = 0; index < current.size(); index++ ) {
		            for (int i = 0; i < 26; i++) {
		                char c = 'a' + i;
		                if (c != current[index]) {
		                	char original = current[index];
		                    current[index] = c;
		                    if (dict.find(current) != dict.end()) {
		                    	// printf("Neighbor :%s for :%s\n" ,current.c_str(), top.c_str());
		                    	remaining.push(current);
		                        oGraph[top].push_back(current);
		                    }
		                    current[index] = original;
		                }
		            }
	        	}
        	}
    	}
    	return -1;
    }
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
 {
        // Similar to normal word ladder
        // Do a BFS from the begin to the en
        // On the way figure out , the minimum cost to each node
        // Also, determine who is a neighbor of who
        // Once we know those , we do a dfs from the beginWord until the endWord, by exmamining neighbors
        // If distance(currentWord) +1 == distance(neighborWord)
        // then continue on DFS, else prune this possibility
        
        
        // Approach 2:
        // Compute the graph of each word to its neighbors
        // mainain a mapping of ach node and minimum cost to get to that node
        // DO a DFS from start to end
        // update cost mapping
        // If we reach end - update minimum and minimum results
        // If cost is the same then append , else replace
        
        unordered_map<string, vector<string>> graph;
        unordered_map<string, int> minCost;

        wordList.push_back(beginWord);


        
        vector<vector<string>> results;
        unordered_set<string> visited;
        vector<string> path;
        auto len = ladderLength(beginWord, endWord, wordList, graph, minCost);
        if (len != -1)
        	dfs(beginWord,  endWord, len, graph, minCost, path, results);
        return results;
    }

    int main() {
    	string beginWord = "hit";
		string endWord = "cog";
vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    	auto result = findLadders(beginWord, endWord, wordList);
    	for (auto vec : result) {
    		for (auto s : vec) {
    			cout << s << ",";
    		}
    		cout << endl;
    	}

    	 beginWord = "a";
		 endWord = "c";
		wordList = {"a","c"};
    	 result = findLadders(beginWord, endWord, wordList);
    	for (auto vec : result) {
    		for (auto s : vec) {
    			cout << s << ",";
    		}
    		cout << endl;
    	}
    }