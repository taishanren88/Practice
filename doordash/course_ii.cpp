#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    // Build a graph of incoming edges
    // Build a graph of outgoing courses
    // Put all nodes which don't have any incoming edges onto the queue
    // while (!empty) , pop it off, visit it, update incoming edge of all neighbors
    // if they become 0, add theirs to the queue
    // return visitedcount == numCourses count
    
    unordered_map<int, int> incoming;
    for (int i = 0; i < numCourses; i++) {
    	incoming[i] = 0;
    }
    unordered_map<int, vector<int> > neighbors;
    for (auto prereq : prerequisites) {
    	auto from = prereq[1];
    	auto to = prereq[0];
    	neighbors[from].push_back(to);
    	incoming[to]++;
    }

    queue<int> visited;
    for (auto kv : incoming) {
    	auto courseId = kv.first;
    	if (kv.second == 0) {
    		visited.push(courseId);
    	}
    }
    vector<int> result;
    while (!visited.empty()) {
    	const auto currentNumClasses = visited.size();
    	for (int i = 0; i < currentNumClasses; i++) {
    		auto currentClass = visited.front();
    		visited.pop();
    		result.push_back(currentClass);
    		// process neighbors
    		for (auto neighbor : neighbors[currentClass]) {
    			incoming[neighbor]--;
    			if (incoming[neighbor] == 0) {
    				visited.push(neighbor);
    			}
    		}
    	}
    }
    if (result.size() != numCourses) {
    	result.clear();
    }
    return result;
}

int main() {
	vector<vector<int>> prereq = {{1,0}};
	auto res = findOrder(2, prereq) ;
	assert(res[0] == 0 && res[1] == 1);

	prereq = {{1,0}, {2,0}, {3,1}, {3,2}};
	res = findOrder(4, prereq) ;
	assert(res.size() == 4);
}
