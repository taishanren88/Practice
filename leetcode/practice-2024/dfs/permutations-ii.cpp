#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<int>& candidates, int index, vector<vector<int>> & results) {
	if (index == candidates.size()) {
		results.push_back(candidates);
		return;
	}
	
	for (int i  = index ; i < candidates.size(); i++ ){
		if (i > index && candidates[i] == candidates[i-1]) {
			continue;
		}
		swap(candidates[i], candidates[index]);
		dfs(candidates,  index + 1, results);
		swap(candidates[i], candidates[index]);
	}
}
vector<vector<int>> permute(vector<int>& candidates) {
	// do a dfs over the array
	// keep track of the current path and reuslt sum
	// if result == target, add to path and return
	// if result > target, return
	// either include or don't include the current value
	vector<int> path;
	sort (candidates.begin(),candidates.end());
	vector<vector<int>> results;
	dfs(candidates, 0, results);
	return results;
}


int main() {
	vector<int> candidates = {1, 1,2};
	auto res = permute(candidates);
	for (auto path : res ) {
		for (auto n : path) {
			cout << n << " , ";
		}
		cout << endl;
	}

}