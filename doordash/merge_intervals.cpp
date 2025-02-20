#include <iostream>
#include <vector>
using namespace std;

bool detectOverlap(vector<int>& a, vector<int>& b) {
	auto aStart = a[0];
	auto aEnd = a[1];

	auto bStart = b[0];
	auto bEnd = b[1];
    return bStart <= aEnd;
}

vector<vector<int> > merge(vector<vector<int> >& intervals) {
    // Detect overlap 
    // If interval a's start time < interval b's start time
    // check if interval b's start time < interval a's end time 
    // If so return true;

	if (intervals.empty()) {
		return vector<vector<int> >();
	}

    sort(intervals.begin() , intervals.end(), [](vector<int>&a , vector<int>&b ) {
    	return a[0] < b[0];
    });
    vector<vector<int> > results;
    results.push_back(intervals[0]);

    for (int i = 1; i <intervals.size(); i++) {
    	auto& currentInterval = intervals[i];
    	if (detectOverlap(results.back(), intervals[i])) {
    		auto& previous = results.back();
    		previous[1] = max (currentInterval[1], previous[1]);
    	} else {
    		results.push_back(currentInterval);
    	}
    }
    return results;
}

int main() {
	vector<vector<int> > intervals = {{1,3},{2,6},{8,10},{15,18}};
	auto res = merge(intervals);
	assert (res == vector<vector<int> >({{1,6},{8,10},{15,18}}));

	vector<vector<int> > intervals2 = {{1,4},{4,5}};
	res = merge(intervals2);
	assert (res == vector<vector<int> >({{1,5}}));
}