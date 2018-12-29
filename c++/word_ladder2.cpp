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

using namespace std;

bool differentByOne(const string& a, const string& b)
{
    // all words have same size: if (a.size() != b.si)
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            if (count == 1)
                return false;
            else
                count = 1;
        }
    }
    return true;
}
    void addNeighbors( string& word, string& target, unordered_set<string>& dict, unordered_set<string>& visited, vector<string>& currPath,  queue<pair<string, vector<string>>>& tovisit)
    {
        for (int i = 0; i < word.size(); i++)
        {
            char original = word[i];
            for (int j = 0; j < 26; j++)
            {
                char possible = 'a' + j;
                word[i] = possible;
                // faster than below of checking aginst every item in the dictionary
                if (dict.find(word) != dict.end() && original != possible)
                {
                    auto str = word;
                    auto v = currPath;
                    v.push_back(str);
                    tovisit.push(std::make_pair(str, std::move(v) ));
                    if (target != word)
                        visited.insert(str);
                }
            }
            word[i] = original;
        }
        // for (auto& str : dict)
        // {
        //     if (differentByOne(word, str))
        //     {
        //         
        //        
        //     }
        // }
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) 
    {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        
        // Do a BFS, add the start word to the queue
        // while (!queue not empty)
        // find all neighbors that are different by one , add them to teh queue, erase from dictionary, so we don't revisit
        /*
        Example: Input:
            beginWord = "hit",
            endWord = "cog",
            wordList = ["hot","dot","dog","lot","log","cog"]

            Queue: hit, Dict: ["hot","dot","dog","lot","log","cog"], dist = 1
            Queue: hot  Dict [ "dot","dog","lot","log","cog"]], dist = 2
            Queue: [dot, lot]  Dict [ ,"dog",,"log","cog"]], dist = 3
            Queue: ["dog","log"]  Dict ["cog"]], dist = 4

        */
        vector<vector<string>> results;
        queue<pair<string, vector<string>>> tovisit;
        queue<pair<string, vector<string>>> nextvisit;
        unordered_set<string> visited;
        tovisit.push(std::make_pair(beginWord, vector<string>(1, beginWord)));
        bool found = false;
        while (!tovisit.empty())
        {
            while (!tovisit.empty())
            {
                auto pair = tovisit.front();
                tovisit.pop();
                if (pair.first == endWord)
                {
                    results.push_back(pair.second);
                    found = true;
                }
                else // find all neighbors and add them
                    addNeighbors(pair.first, endWord, dict, visited, pair.second, nextvisit);
            }
            if (!visited.empty())
            {
                for (const string& s : visited)
                    dict.erase(s);
                 visited.clear();
            }
            if (found)
                break;
            tovisit = std::move(nextvisit);
            nextvisit =  queue<pair<string, vector<string>>>();
        }
        return results;
    }
    
    int main()
    {
        vector<string> v = {"hot","dot","dog","lot","log","cog"};

        vector<vector<string>> a = findLadders("hit", "cog",v );
        for (auto & v : a)
        {
            for (string& s: v)
                cout << s << ",";
            cout <<endl;
        }
         v = {"a", "b" , "c"};
        auto b = findLadders("a", "c",v );
        for (auto & v : b)
        {
            for (string& s: v)
                cout << s << ",";
            cout <<endl;
        }
        v =  {"ted","tex","red","tax","tad","den","rex","pee"};
        auto c = findLadders("red","tax", v);
         for (auto & v : c)
        {
            for (string& s: v)
                cout << s << ",";
            cout <<endl;
        }
    }
