#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
	using Interval = vector<int>;

	sort(intervals.begin(), intervals.end() , [](Interval & a, Interval & b ) {
		return a[0] < b[0];
	});
	vector<Interval> results;
	if (intervals.empty()) {
		return results;
	}

	results.push_back(intervals[0]);
	for (int i = 1; i < intervals.size() ; i++) {
		auto& previous = results.back();
		auto prevEnd = previous[1];
		auto currStart = intervals[i][0];
		if (currStart <= prevEnd) {
			previous[1] = max(previous[1], intervals[i][1]);
		} else {
			results.push_back(intervals[i]);
		}
	}
	return results;
}
int main() {
	vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
	auto res = merge(intervals);
	assert(res[0][0] == 1 && res[0][1] == 6
	       && res[1][0] == 8 && res[1][1] == 10
	       && res[2][0] == 15 && res[2][1] == 18);

	intervals = {{1, 4}, {4, 5}};
	res = merge(intervals);
	assert(res[0][0] == 1 && res[0][1] == 5);


}