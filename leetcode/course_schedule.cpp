 #include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

 vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> graph;
        unordered_map<int, int> incomingCount;
        for (int i = 0; i < numCourses; i++)
        {
            graph[i] = vector<int>();
            incomingCount[i] = 0;
        }

        // [B,A] : A->B , B depends on A
        for (const auto& req: prerequisites)
        {
            // A -> B
            auto a = req[1];
            auto b = req[0];

            graph[a].push_back(b);
            incomingCount[b]++;
        }
        
        queue<int> toprocess;
        for (auto kv : incomingCount)
        {
            if (kv.second == 0)
                toprocess.push(kv.first);
        }

        vector<int> results;
        while (!toprocess.empty())
        {
            auto nextNode = toprocess.front();
            toprocess.pop();
            results.push_back(nextNode);
            for (auto neighbor :graph[nextNode])
            {
                incomingCount[neighbor]--;
                if (incomingCount[neighbor] == 0)
                    toprocess.push(neighbor);
            }
        }
        return results.size() == numCourses ? results : vector<int>();
    }

    int main() {
        vector<vector<int>> a = {{1,0},{2,0},{3,1},{3,2}};
        auto res  = findOrder(4, a);
        for (auto i : res)
            cout << i << ",";
    }