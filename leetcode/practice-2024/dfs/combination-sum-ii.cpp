#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<int>& candidates, vector<int>& path, vector<vector<int>> & results, int index, int sum, int target) {
	if (sum == target ) {
		// cout << "found" << endl;
		results.push_back(path);
		return;
	}
	if (sum > target  ) {
		return;
	}
	
	for (int i  = index ; i < candidates.size(); i++ ){
		if (i > index && candidates[i] == candidates[i-1] ) {
				continue;
			} 
		path.push_back(candidates[i]);
		dfs(candidates, path, results, i + 1, sum + candidates[i], target);
		path.pop_back();
	}
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	// do a dfs over the array
	// keep track of the current path and reuslt sum
	// if result == target, add to path and return
	// if result > target, return
	// either include or don't include the current value
	vector<int> path;
	vector<vector<int>> results;
	sort(candidates.begin(), candidates.end());
	dfs(candidates, path, results, 0 , 0, target);
	return results;
}


int main() {
	vector<int> candidates = {10,1,2,7,6,1,5};
	auto res = combinationSum(candidates, 8);
	for (auto path : res ) {
		for (auto n : path) {
			cout << n << " , ";
		}
		cout << endl;
	}

}