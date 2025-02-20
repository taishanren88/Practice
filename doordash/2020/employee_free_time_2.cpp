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
	// sort all the intervals by start point
	// at each point check if the current interval overlaps, if it does , merge the "previous" one 
	// if not then, we have a free time.
	vector<Interval> sortedIntervals;
	for (auto& employeeSchedule : schedule) {
		for (auto& slot : employeeSchedule) {
			sortedIntervals.push_back(slot);
		}
	}
	sort(sortedIntervals.begin(), sortedIntervals.end(), [](const Interval& a, const Interval& b) {
		return a.start < b.start;
	});

	Interval previousInterval = sortedIntervals[0];
	vector<Interval> results;
	for (int i = 1 ; i < sortedIntervals.size(); i++) {
		auto currInterval = sortedIntervals[i];
		if (currInterval.start <= previousInterval.end) {
			// overlap
			previousInterval.end = max(previousInterval.end, currInterval.end);
		} else {
			// no overlap
			results.emplace_back(previousInterval.end, currInterval.start);
			previousInterval = currInterval;
		}
	}
	return results; 

}

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