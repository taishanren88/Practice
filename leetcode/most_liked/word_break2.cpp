#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

using Path = vector<int>;

void dfs(string s, int currentIndex,  unordered_map<int, vector<Path > > &levels2Paths, 
						unordered_set<string>& wordDict) {

	if (currentIndex == s.size()) {
		if ( levels2Paths.find(currentIndex) == levels2Paths.end()) {
			levels2Paths[currentIndex].push_back(Path());
			return;
		}
	}

	if (levels2Paths.find(currentIndex) != levels2Paths.end()) {
		return;
	}

	 levels2Paths[currentIndex] = vector<Path>(); 

	for (int i = currentIndex ; i < s.size(); i++ ) {
		string word = s.substr(currentIndex, i - currentIndex + 1);
		if (wordDict.find(word) != wordDict.end()) {
			dfs(s, i + 1, levels2Paths, wordDict); 
			for (Path& path : levels2Paths[i+1]) {
				Path newPath ;
				newPath.push_back(i+1);
				newPath.insert(newPath.begin() + 1, path.begin(), path.end());
				levels2Paths[currentIndex].push_back(newPath);
			}
		}
	}
}

vector<string> wordBreak(string s,vector<string>& wordDict) {
    
    // Treat every index like a vertex of a graph
    // Do a DFS from start to end
    // At each level, if we found a successful path to the end, append those to 
    // "levels2Paths"
    // If there's an entry for a level it means , we've visisted it already

	// Transform all the valid paths to strings
	unordered_set<string> sortedDict(wordDict.begin(), wordDict.end());
	unordered_map<int, vector<Path > > levels2Paths;
	dfs(s, 0, levels2Paths, sortedDict);
	vector<string> results;

	auto transform =[&results, &s, &levels2Paths]() {
		for (auto& path : levels2Paths[0]) {
			string result;
			int startIndex = 0;
			for (int i = 0; i < path.size(); i++) {
				auto index = path[i];
				result += s.substr(startIndex, index - startIndex);
				if ( i < path.size() - 1) {
					result += " ";
				}
				startIndex = index;
			}
			results.push_back(result);
		}
	};
	transform();
		
    return results;
}	

int main() {

string s =  "catsanddog";
vector<string> wordDict = { "cat", "cats", "and", "sand", "dog"};
unordered_set<string> sortedDict(wordDict.begin(), wordDict.end());

unordered_map<int, vector<Path> > graph;
dfs(s, 0, graph ,  sortedDict);

vector<int> path1 = {3,7,10};
vector<int> path2 = {4,7,10};

assert(graph[0].size() == 2);
assert(graph[0][0].size() == path1.size()
		&& graph[0][0][0] == 3 && graph[0][0][2] == 10);
assert(graph[0][1].size() == path2.size()
		&& graph[0][1][0] == 4 && graph[0][1][2] == 10);

auto results = wordBreak(s, wordDict);
assert(results[0] == "cat sand dog");
assert(results[1] == "cats and dog");

s = "catsandog";
graph.clear();
dfs(s, 0, graph,  sortedDict);
assert(graph[0].empty());

s = "pineapplepenapple";
wordDict = {"apple", "pen", "applepen", "pine", "pineapple"};
sortedDict = unordered_set<string>(wordDict.begin(), wordDict.end());
results = wordBreak(s, wordDict);
assert(results[0] == "pine apple pen apple");
assert(results[1] == "pine applepen apple");
assert(results[2] == "pineapple pen apple");

}