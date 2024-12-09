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
		// cout << " grater" << endl;
		return;
	}
	if (index == candidates.size()) {
		// cout << "HER" << endl;
		return;
	}

	path.push_back(candidates[index]);
	sum += path.back();
	dfs(candidates, path, results, index, sum, target);
	sum -= path.back();
	path.pop_back();
	dfs(candidates, path, results, index + 1, sum, target);
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	// do a dfs over the array
	// keep track of the current path and reuslt sum
	// if result == target, add to path and return
	// if result > target, return
	// either include or don't include the current value
	vector<int> path;
	vector<vector<int>> results;
	dfs(candidates, path, results, 0 , 0, target);
	return results;
}

int main() {
	vector<int> candidates = {2,3,6,7};
	auto res = combinationSum(candidates, 7);
	for (auto path : res ) {
		for (auto n : path) {
			cout << n << " , ";
		}
		cout << endl;
	}

}