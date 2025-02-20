#include <iostream>
#include <set>
using namespace std;


struct Interval {
	Interval(int aMaxVal) 
	:maxVal(aMaxVal)
	{

	}
	bool operator ()(const pair<int,int>& a, const pair<int,int>& b)const {
		auto getDistance=[&](const pair<int,int>& p) {
			if (p.first == -1)
				return p.second;
			else if (p.second == maxVal)
				return maxVal - p.first - 1;
			else {
				return (p.second - p.first) / 2;
			}
		};
		auto aDist = getDistance(a);
		auto bDist = getDistance(b);
		// if (aDist == bDist)
		// 	return a.first < b.first;
		return aDist > bDist;
	}
	int maxVal;
};

class ExamRoom {
public:
    ExamRoom(int N)
    :availableIntervals(Interval(N)), maxVal(N) {
     // Create a set of available intervals and have it be sorted by distance, where t        he top is the one with the largest distance
    // Whenever someone comes in , remove the first entry from the set and gets it seat 
    // initially add [-1, N] as the first interval
    // Whenever a seat is taken split it into two intervals :
    // If seat is 0 , split into [-1, 0] and [0, end]
    // If seat is end, split into [start, N-1], [N-1, end]
    // Else split into [0, mid], [mid, end]
    // During leave(), find the interval which contains this seat as tail and head 
    // [start, target], [target, end]. Remove those two and merge them back.
        availableIntervals.insert(make_pair(-1, N));
    }
    
    int seat() {
        auto first = availableIntervals.begin();
        auto getSeat=[&](pair<int,int> p) {
        	if (p.first == -1)
        		return 0;
        	else if (p.second == maxVal)
        		return maxVal - 1;
        	else {
        		return (p.second + p.first) / 2;
        	}
        };

        auto bestPair = *(availableIntervals.begin());
        availableIntervals.erase(bestPair);
        auto seat = getSeat(bestPair);
        availableIntervals.insert(make_pair(bestPair.first, seat));
        availableIntervals.insert(make_pair(seat, bestPair.second));
        printf("size :%d\n", availableIntervals.size());
        return seat;
    }
    
    void leave(int p) {
    	pair<int,int> tail;
    	pair<int,int> head;
    	bool foundTail = false;
    	bool foundHead = false;
    	for (auto interval : availableIntervals) {
    		printf("Valid i :%d, %d\n", interval.first, interval.second);
    		if (interval.second == p) {
    			tail = interval;
    			 printf("Found tail:%d,%d\n", tail.first, tail.second);

    			foundTail = true;
    		}
    		if (interval.first == p) {
    			head = interval;
    			printf("Found head:%d,%d\n", head.first, head.second);
    			foundHead = true;
    		}
    		if (foundTail && foundHead) {
    			break;
    		}
    	}
    	availableIntervals.erase(tail);
    	availableIntervals.erase(head);
    	availableIntervals.insert(make_pair(tail.first, head.second));

    }
    set<pair<int,int>, Interval> availableIntervals;
    int maxVal;
};

int main() {
	ExamRoom examRoom(10);
	assert(examRoom.seat() == 0);
	assert(examRoom.seat() == 9);
	assert(examRoom.seat() == 4);
	assert(examRoom.seat() == 2);
	examRoom.leave(4);
	assert(examRoom.seat() == 5);
}