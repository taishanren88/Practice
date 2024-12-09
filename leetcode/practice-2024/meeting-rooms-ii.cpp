#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int minMeetingRooms(vector<vector<int>>& intervals) {
	// Sort the intervals by start time
	// Create a multiset , where we managet sorted end times
	// If we encounter an interval, checking the begin of the muliset. If it's < current one, no new room is needed
    
    std::sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b){
    	return a[0] < b[0];
    });
    std::multiset<int> endTimes;
    int numIntervals = 0;
    for (auto interval : intervals) {
    	if (!endTimes.empty() && *endTimes.begin() <= interval[0]) {
    		endTimes.erase(endTimes.begin());
    		endTimes.insert(interval[1]);
    	} else {
    		endTimes.insert(interval[1]);
    		numIntervals++;
    	}
    }
    return numIntervals;

}

int main() {
	vector<vector<int>> intervals{ {0,30}, {5,10}, {15,20}};
	cout << minMeetingRooms( intervals) << endl;

	intervals = {{7,10}, {2,4}};
	cout << minMeetingRooms(intervals) << endl;
}