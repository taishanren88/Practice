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
    // sort all of the intervals by start time
    // loop through all intervals and merge all of the overlapping ones
    // at the very end loop through the intervals, and get the difference between each one pair-wise
    // if next start -  previous end  >0 , then create an interval of (previous end, next start)

    vector<Interval> sortedIntervals;
    for (int i = 0; i < schedule.size(); i++) {
        for (int j = 0; j < schedule[i].size(); j++) {
            sortedIntervals.push_back(schedule[i][j]);
        }
    }
    sort(sortedIntervals.begin(), sortedIntervals.end() , [](Interval& a, Interval& b) {
        if (a.start ==  b.start)
            return a.end < b.end;
        return a.start <= b.start;
    });
    
    auto detectOverlap =[](Interval&a, Interval&b) {
        return b.start <= a.end;
    };
    
    vector<Interval> overlappingIntervals;
    overlappingIntervals.push_back(sortedIntervals[0]);
    // printf("START IS :%d, %d\n", sortedIntervals[0].start, sortedIntervals[0].end);
    for (int i = 1; i < sortedIntervals.size(); i++) {
        if (detectOverlap(overlappingIntervals.back(), sortedIntervals[i])) {
            auto previousEnd = overlappingIntervals.back().end;
            // printf("DETECTEd OVERLAP :%d, %d\n", previousEnd, sortedIntervals[i].start);
            overlappingIntervals.back().end = max(previousEnd, sortedIntervals[i].end);
        } else {
        	// printf("PUSH :%d, %d\n", sortedIntervals[i].start, sortedIntervals[i].end);
            overlappingIntervals.push_back(sortedIntervals[i]);
        }
    }

    {
    	// for (int i = 0; i < overlappingIntervals.size(); i++ )
    	// {
    	// 	printf("%d, %d,", overlappingIntervals[i].start, overlappingIntervals[i].end);
    	// }
    }
   
    vector<Interval> results;
    for (int i =1; i < overlappingIntervals.size(); i++) {
      if (overlappingIntervals[i].start - overlappingIntervals[i-1].end >= 1) {
          results.push_back(Interval(overlappingIntervals[i-1].end, overlappingIntervals[i].start));
      }
    }
    return results;
}

vector<vector<Interval> > serialize (vector <vector<vector<int> > > schedule ) {
	vector<vector<Interval>> results;
	for (auto & employee : schedule ) {
		results.push_back(vector<Interval>());
		for (auto &times : employee) {
			results.back().push_back(Interval(times[0], times[1]));
		}
	}
	return results;
}

void printResult(vector<Interval>& results) {
	for (auto interval : results) {
		printf("%d,%d, ", interval.start, interval.end);
	}
}
int main() {
	vector<vector<vector<int>>> schedule = { { {1,2}, {5,6}  }, { {1,3}} , {{4,10}} };
	auto scheduleSerialized = serialize(schedule);
	// for (auto employee : scheduleSerialized) {
	// 	for (auto interval : employee) {
	// 		printf("%d,%d, ", interval.start, interval.end);
	// 	}
	// 	printf("\n");
	// }
	 
	auto results = employeeFreeTime(scheduleSerialized);
	printResult(results);

	assert(results[0].start == 3 && results[0].end == 4);

	schedule = {{{1,3},{6,7}},{{2,4}},{{2,5},{9,12}}};
	scheduleSerialized = serialize(schedule);
	results = employeeFreeTime(scheduleSerialized);
	printResult(results);
	assert(results[0].start = 5 && results[0].end == 6
			&& results[1].start == 7 && results[1].end == 9);
}