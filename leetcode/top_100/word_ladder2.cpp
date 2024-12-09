#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;
void print(vector<string>& path) {
    for (auto s : path) {
        cout << s << ",";
    }
    cout << endl;
}
vector<vector<string>> helper(string beginWord, string endWord, unordered_set<string>& wordList) {
    // Maintain a queue containing a vector of paths
    // At each point , we will do a BFS using all of the previous paths
    // For each path, pop it off of the queue
    // Take the last word from each path, find all of its 1-letter-off neighbors
    // At the start of each iteration, also need to remove the last word from the wordList to ensure we don't add it back
    // Each time we concatenate a word , take the old path and duplicate with the new word
    // If we reach the end we are done, store the minimum level.
    // If any path is larger than this path do not consider it

    int minLevel = INT_MAX;
    queue<vector<string>> toProcess;
    toProcess.push(vector<std::string>());
    toProcess.front().push_back(beginWord);
    vector<vector<string>> results;
    unordered_set<string> visited;
    wordList.erase(beginWord);
    while (!toProcess.empty()) {
        int queueLen = toProcess.size();
        if (minLevel != INT_MAX) {
            return results;
        }
        for (string w : visited) {
            wordList.erase(w);
        }
        visited.clear();
        for (int i = 0; i < queueLen; i++) {
            auto lastPath = toProcess.front();
            toProcess.pop();
            auto lastWordInPath = lastPath.back();

            for (int k = 0; k < lastWordInPath.size(); k++) {
                char original = lastWordInPath[k];
                for (int m = 0 ; m < 26; m++) {
                    char changeLetter = 'a' + m;
                    if (changeLetter != original) {
                        lastWordInPath[k] = changeLetter;
                        if (wordList.find(lastWordInPath) != wordList.end()) {
                            auto newPath = lastPath;
                            newPath.push_back(lastWordInPath);
                            if (lastWordInPath == endWord) {
                                int level = newPath.size();
                                if (level <= minLevel) {
                                    minLevel = level;
                                    results.push_back(newPath);
                                }
                            } else {
                                toProcess.push(newPath);
                            }
                            visited.insert(lastWordInPath);
                            // print(lastPath);

                        }
                        lastWordInPath[k] = original;
                    }
                }
            }
        }
    }
    return results;
}


vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    // Find the minimum ladder length - Do a BFS of all the words until we find the end
    // Get the minimum cost to each neighbor starting from 0 as the first word
    // Get the graph
    unordered_set<string> wordListDict;
    for (auto& word : wordList) {
        wordListDict.insert(word);
    }
    auto results = helper(beginWord, endWord, wordListDict);
    return results;
}


using WordCostGraph = unordered_map<string, int>;
using Word2NeighborGraph = unordered_map<string, vector<string>>;

int minLadderLength (string beginWord, string endWord, unordered_set<string>& wordList,
                     WordCostGraph& minCosts,
                     Word2NeighborGraph&graph) {
    // Maintain a queue containing a vector of paths
    // At each point , we will do a BFS using all of the previous paths
    // For each path, pop it off of the queue
    // Take the last word from each path, find all of its 1-letter-off neighbors
    // At the start of each iteration, also need to remove the last word from the wordList to ensure we don't add it back
    // Each time we concatenate a word , take the old path and duplicate with the new word
    // If we reach the end we are done, store the minimum level.
    // If any path is larger than this path do not consider it

    int minLevel = INT_MAX;
    queue<string> toProcess;
    toProcess.push(beginWord);
    int minCost = -1;
    minCosts[beginWord] = 0;
    wordList.erase(beginWord);
    while (!toProcess.empty()) {
        int queueLen = toProcess.size();
        minCost++;
        unordered_set<string> toVisit;
        for (int i = 0; i < queueLen; i++) {
            auto currentWord = toProcess.front();
            toProcess.pop();
            if (currentWord == endWord) {
                return minCost;
            }
            for (int k = 0; k < currentWord.size(); k++) {
                char original = currentWord[k];
                for (int m = 0 ; m < 26; m++) {
                    char changeLetter = 'a' + m;
                    if (changeLetter != original) {
                        auto nextWord = currentWord;
                        nextWord[k] = changeLetter;
                        if (wordList.find(nextWord) != wordList.end()) {
                            graph[currentWord].push_back(nextWord);
                            minCosts[nextWord] = minCost + 1;
                            toVisit.insert(nextWord);
                        }
                    }
                }
            }
        }
        for (auto visit : toVisit) {
            wordList.erase(visit);
            toProcess.push(visit);
        }
    }
    return -1;
}

void dfs(string currentWord, string endWord, vector<string>& path, vector<vector<string>>& results,
         WordCostGraph& minCosts, Word2NeighborGraph& graph, const int minCost) {
    if (currentWord == endWord) {
        results.push_back(path);
        return;
    }
    for (auto& neighbor : graph[currentWord]) {
        if (minCosts[currentWord] + 1 == minCosts[neighbor]) {
            path.push_back(neighbor);
            dfs(neighbor, endWord, path, results, minCosts, graph, minCost);
            path.pop_back();
        }
    }
}

vector<vector<string>> findLadders2(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordListDict;
    for (auto& word : wordList) {
        wordListDict.insert(word);
    }
    WordCostGraph minCosts;
    Word2NeighborGraph graph;
    auto minCost  = minLadderLength ( beginWord,  endWord,  wordListDict,
                                      minCosts,
                                      graph);
    vector<string> path = {beginWord};
    vector<vector<string>> results;
    dfs(beginWord, endWord, path, results, minCosts, graph, minCost);

    return results;
}

int main() {
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    auto result1 = findLadders("hit", "cog", wordList);
    for (auto result : result1) {
        print(result);
        cout << endl;
    }
    vector<string> wordList2 = {"a", "b", "c"};
    // auto result2 = findLadders("a", "c", wordList2);
    // for (auto result : result2) {
    //     print(result);
    //     cout << endl;
    // }

    unordered_set<string> wordListAsDict1(wordList.begin(), wordList.end());
    WordCostGraph minCost;
    Word2NeighborGraph graph;
    assert(minLadderLength("hit", "cog", wordListAsDict1, minCost, graph) == 4);

    unordered_set<string> wordListAsDict2(wordList2.begin(), wordList2.end());
    WordCostGraph minCost2;
    Word2NeighborGraph graph2;
    assert(minLadderLength("a", "c", wordListAsDict2, minCost2, graph2) == 1);

    WordCostGraph minCost3;
    Word2NeighborGraph graph3;

    unordered_set<string> wordListAsDict3(wordList.begin(), wordList.end());

    // minLadderLength("hit", "cog", wordListAsDict3, minCost3, graph3) ;
    // cout << " ###" << endl;
    // for (auto& kv : graph3) {
    //     cout << kv.first ;
    //     for (auto neighbor : kv.second) {
    //         cout << ", " << neighbor;
    //     }
    //     cout << endl;
    // }
    // cout << " ###" << endl;

    auto result11 = findLadders2("hit", "cog", wordList);
    for (auto result : result11) {
        print(result);
        cout << endl;
    }
    auto result22 = findLadders2("a", "c", wordList2);
    for (auto result : result22) {
        print(result);
        cout << endl;
    }

    vector<string> wordList3 = {"hot", "dog", "dot"};
    unordered_set<string> wordList3AsDict (wordList3.begin(), wordList3.end());
    WordCostGraph minCost33;
    Word2NeighborGraph graph33;
    minLadderLength("hot", "dog", wordList3AsDict, minCost33, graph33) ;
    cout << " ###" << endl;
    for (auto& kv : graph33) {
        cout << kv.first ;
        for (auto neighbor : kv.second) {
            cout << ", " << neighbor;
        }
        cout << endl;
    }
    for (auto kv : minCost33 ) {
        cout << kv.first << ", " << kv.second ;
        cout << endl;
    }
     cout << " ###" << endl;

    auto result23 = findLadders2("hot", "dog", wordList3);
    for (auto result : result23) {
        print(result);
        cout << endl;
    }

    // Test min lader length
}