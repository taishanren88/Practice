#include <iostream>
#include <vector>

using namespace std;

// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
	// Put all "free" intervals in a single vector
	// sort all intervals by start time
	// merge all overlapping intervals into a single array
	// find the difference bteween each point
	vector<Interval> sortedIntervals;
	for (auto& employeeSchedule : schedule) {
		for (auto &i : employeeSchedule) {
			sortedIntervals.push_back(i);
		}
	}
	sort(sortedIntervals.begin(), sortedIntervals.end(), [](const Interval& a, const Interval& b) {
		if (a.start == b.start) {
			return a.end < b.end;
		} else {
			return a.start < b.start;
		}
	});
	vector<Interval> mergedIntervals;
	mergedIntervals.push_back(sortedIntervals[0]);
	for (int i = 1; i < sortedIntervals.size(); i++) {
		auto& interval = sortedIntervals[i];
		auto& prev = mergedIntervals.back();
		if (interval.start < prev.end) {
			prev.end = max(prev.end, interval.end);
		} else {
			mergedIntervals.push_back(interval);
		}
	}
	vector<Interval> results;
	for (int i = 1 ; i < mergedIntervals.size() ; i++) {
		auto& curr = mergedIntervals[i];
		auto& prev = mergedIntervals[i-1];

		if (curr.start - prev.end >= 1) {
			results.emplace_back(prev.end, curr.start);
		}
	}
	return results;
}
// [1,2],[1,3],[4,10],[5,6] -> [1,3], [4,10]

vector<vector<Interval>> toInterval( const  vector<vector<pair<int,int>>>& schedule) {
	vector<vector<Interval>> result;
	for (auto& employeeSchedule : schedule) {
		vector<Interval> employeeConverted;
		for (auto &i : employeeSchedule) {
			employeeConverted.emplace_back(i.first, i.second);
		}
		result.push_back(employeeConverted);
	}
	return result;
}
void print(vector<Interval> intervals) {
	for (auto& i : intervals ) {
		cout << i.start << ',' << i.end << endl;
	}
}
int main() {
	vector<vector<pair<int,int>>> schedule = { {{ 1,2}, {5,6}}, { {1,3} }, {{4,10}} };
	print(employeeFreeTime(toInterval(schedule)));

	 schedule = { {{ 1,3}, {6,7}}, { {2,4} }, {{2,5}, {9,12}} };
	print(employeeFreeTime(toInterval(schedule)));

	 schedule = { {{ 1,3}, {5,6}}, { {2,3} }, {{3,4}} }; // [1,3] [3,4],
	print(employeeFreeTime(toInterval(schedule)));


}