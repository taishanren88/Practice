#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std; 


bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
// Looks like a graph traversal to me
// Build a graph using the prerequisites
//  Build a prerequisite count for each node
// Iterate over the graph by queieng  nodes with 0 incoming edges
// Each node has a prequisite count
// For each node (A -> B, where B dependent on A first), execute A 
// and prequisite count of neighbor.
//  If any neighbor has a count of 0, queue it also 
//  //If we executed all nodes, we're good
//  

	unordered_map<int,int> incomingCounts;
	unordered_map<int, vector<int> > outgoing;
	for (int i = 0; i <  numCourses; i++){
		incomingCounts[i] = 0;
	}
	for (int i = 0; i < prerequisites.size(); i++){
		auto& pair = prerequisites[i];
		// (first, second), where second -> first
		incomingCounts[pair[0]]++;
		outgoing[pair[1]].push_back(pair[0]);
	}

	// Iterate over graph
	queue<int> toprocess;
	for (auto& kv: incomingCounts) {
		if (kv.second == 0) {
			cout << "kv. first "<<kv.first;
			toprocess.push(kv.first);
		}
	}

	std::vector<int> results;
	while (!toprocess.empty()) {
		auto front = toprocess.front();
		toprocess.pop();
		cout << front << endl;
		results.push_back(front);
		// find all of its ougoing neighbors
		auto neighbors = outgoing[front];
		for (int i = 0; i < neighbors.size(); i++){
			cout << "check neighbors " << endl;
			incomingCounts[neighbors[i]]--;
			if (incomingCounts[neighbors[i]] == 0) {
				toprocess.push(neighbors[i]);
			}
		}
	}

	return results.size() == numCourses;
}

int main() {
	auto preRequisites = vector<vector<int>>{{0,1}};
	cout << canFinish(2, preRequisites) << endl;
		auto preRequisites2 = vector<vector<int>>{{0,1}, {1,0}};

	cout << canFinish(2, preRequisites2) << endl;

}