#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void dfs(string s, int startIndex, unordered_map<int, vector<string> > & paths, const unordered_set<string>& wordDictLookup) {
    if (startIndex == s.size()) {
        if (paths.find(startIndex) == paths.end()) {
            paths[startIndex] = vector<string>({""});
        }
        return;
    }
    if (paths.find(startIndex) != paths.end()) {
        return;
    }
    printf("START INDEX :%d\n", startIndex);
    paths[startIndex] = vector<string>();
    for (int i = startIndex; i < s.size(); i++) {
        auto word = s.substr(startIndex, i - startIndex +1);
        if (wordDictLookup.find(word) != wordDictLookup.end()) {
        	printf("FOUND WORD :%s\n", word.c_str());
            dfs(s, i +1, paths, wordDictLookup);
            for (const auto& path : paths[i + 1]) {
                paths[startIndex].push_back(word + " " + path);
            }
        }  
     }
}

vector<string> wordBreak(string s, vector<string>& wordDict) {
    // Do a DFS 
    // At each start index, maintain a mapping of valid paths from current index to the end
    // If there are valid paths from going to the next start, append those paths that start at the next level to the current path
    // At the end, return all the mappings from "0"
    unordered_map<int, vector<string> > paths;
    unordered_set<string> wordDictLookup (wordDict.begin(), wordDict.end());
    dfs(s, 0,  paths, wordDictLookup);
    // remove trailing space    
    vector<string> results;
    for (auto path : paths[0]) {
        results.push_back(path.substr(0, path.size() -1));
    }
    return results;
}

int main() {

string s =  "catsanddog";
vector<string> wordDict = { "cat", "cats", "and", "sand", "dog"};
auto results = wordBreak(s, wordDict);
assert(results[0] == "cat sand dog");
assert(results[1] == "cats and dog");

s = "pineapplepenapple";
wordDict = {"apple", "pen", "applepen", "pine", "pineapple"};
results = wordBreak(s, wordDict);
assert(results[0] == "pine apple pen apple");
assert(results[1] == "pine applepen apple");
assert(results[2] == "pineapple pen apple");

}