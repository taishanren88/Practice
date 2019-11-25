
//
//  main.cpp
//  Test
//
//  Created by jimmy on 5/20/19.
//  Copyright © 2019 jimmy. All rights reserved.
//

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <vector>
#include <string>
using namespace std;


struct TrieNode
{
    TrieNode()
    :children(26, nullptr), endsHere(false) {
        
    }
    bool endsHere;
    vector<TrieNode*> children;
};

class Trie
{
public:
    
    Trie(vector<string>& words) {
        buildTrie(words);
    }
    
    bool startsWith(string prefix) {
        auto ret = getNodeWithPrefix(prefix);
        return ret != nullptr;
    }
    bool exists(string word) {
        auto ret = getNodeWithPrefix(word);
        return ret && ret->endsHere;
    }
    TrieNode* getNodeWithPrefix(string prefix) {
        auto curr = &root;
        for (char letter : prefix) {
            auto index = letter - 'a';
            if (!curr->children[index]) {
                return nullptr;
            }
            curr = curr->children[index];
        }
        return curr;
    }
    void buildTrie(vector<string>& words) {
        for (auto& word : words) {
            auto* curr = &root;
            for (auto letter : word) {
                auto index = letter - 'a';
                if (!curr->children[index]) {
                    curr->children[index] = new TrieNode();
                }
                curr = curr->children[index];
            }
            curr->endsHere = true;
        }
    }
    
private:
    TrieNode root;
    
};

class Solution {
public:
    
    void dfs(vector<vector<char>>& board,unordered_set<string>& results, string curr, int r, int c, Trie& dictionary ) {
        // Terminating conditions:
        // Check validity of bounds
        // Check if current word hasn't been visited
        // Check if current word exists in trie, if so add it

        if (r < 0 || r >= board.size() 
            || c < 0 || c >= board[r].size()
            || board[r][c] == '\0') {
            return;
        }
        string possible = curr + board[r][c];
        if (!dictionary.startsWith(possible)) {
            return;
        }
        if (dictionary.exists(possible)) {
            results.insert(possible);
        }

        auto original = board[r][c];
        board[r][c] = '\0';
        dfs(board, results, possible,  r -1 , c, dictionary);
        dfs(board, results, possible,  r + 1 , c, dictionary);
        dfs(board, results, possible,  r , c - 1, dictionary);
        dfs(board, results, possible,  r , c + 1, dictionary);
        board[r][c] = original;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        
        Trie dictionary(words);
        unordered_set<string> results;
        for (int i = 0; i < board.size(); i++ ) {
            for (int j = 0; j < board[i].size() ; j++ ) {
                dfs(board, results, "", i, j, dictionary);
            }
        }
        return vector<string>(results.begin(), results.end());
    }
};

int main(int argc, const char * argv[]) {
    vector<string> dict {"oath", "pea","eat","rain"};
    Trie testTrie(dict);
    assert(!testTrie.exists("oat"));
    assert(testTrie.startsWith("oat"));
    assert(testTrie.exists("oath"));
    assert(!testTrie.startsWith("a"));
    assert(testTrie.startsWith(""));
    Solution s; 

    
    return 0;
}
