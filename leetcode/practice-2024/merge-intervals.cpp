#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    
    // Sort the vector . First by earliest start and if =, then by end time 
    // An intervl is overlapping of int[i]_start <= int[i-1]_end
    // [0, 1] , [2,3]
    // [0,1],[1,2] => [1,2]

	std::sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>&b) {
		return a[0] < b[0];
	});
	if (intervals.empty()) {
		return {};
	}
	vector<vector<int>> results = {intervals[0]};
	for (int i = 1; i < intervals.size(); i++){
		auto prev = results.back()[1];
		if (intervals[i][0] <=results.back()[1]) {
			results.back()[1] = std::max(results.back()[1], intervals[i][1]);
		} else {
			results.push_back(intervals[i]);
		}
	}
    return results;
}
int main(){
	vector<vector<int>> intervals{ {1,3},{2,6},{8,10},{15,18}};
	auto res = merge(intervals);
		for (int i = 0; i< res.size(); i++){
			cout << "{ " << res[i][0] <<" , " << res[i][1] << " }, ";
		}
}