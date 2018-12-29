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
    void addNeighbors( string& word, unordered_set<string>& dict, queue<string>& tovisit)
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
                    tovisit.push(str);
                    dict.erase(str);
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

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
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
        queue<string> tovisit;
        queue<string> nextvisit;
        tovisit.push(beginWord);
        int dist = 0;
        while (true)
        {
            while (!tovisit.empty())
            {
                auto str = tovisit.front();
                tovisit.pop();
                if (str == endWord)
                    return dist+1;
                else // find all neighbors and add them
                    addNeighbors(str,dict, nextvisit);
            }
            tovisit = std::move(nextvisit);
            nextvisit = queue<string>();
            dist++;
        }
        return 0;
    }
    
    int main()
    {
        vector<string> v = {"hot","dot","dog","lot","log","cog"};
        assert(ladderLength("hit", "cog",v ) == 5);
        v = {"b" , "c"};
        cout <<ladderLength("a", "c",v );
         assert(ladderLength("a", "c",v ) == 2);

        
    }
