#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<int>& candidates, int target, int pos, vector<int>& path, vector<vector<int>>& results, int currentSum) {
	if (currentSum > target) {
		return;
	}
	if (currentSum == target) {
		results.push_back(path);
	}
	for (int i = pos ; i < candidates.size(); i++ ) {
		path.push_back(candidates[i]);
		dfs(candidates, target, i, path, results, currentSum + candidates[i]);
		path.pop_back();
	}
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	// Do a DFS
	// At each point consider whether the current path sum adds up to the given target
	// If so , add it to the resulting path
	// At each point, iterate over from teh current position to the rest all of the candidates
	// Incldue and don't include the current value
	vector<int> path;
	vector<vector<int>> results;
	dfs(candidates, target , 0, path, results, 0);
	return results;
}
int main() {
	auto print = [] (vector<vector<int>> result) {
		for (auto r : result) {
			for (auto num : r) {
				cout << num << ",";
			}
			cout << endl;
		}
		cout << endl;
	};
	vector<int> candidates = {2, 3, 6, 7};
	auto res = combinationSum(candidates, 7);
	print(res);

	candidates = {2, 3, 5};
	res = combinationSum(candidates, 8);
	print(res);


	candidates = {2};
	res = combinationSum(candidates, 1);
	print(res);

		candidates = {1};
	res = combinationSum(candidates, 1);
	print(res);


		candidates = {1};
	res = combinationSum(candidates, 2);
	print(res);
}