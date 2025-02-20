#include <iostream>
#include <map>
#include <cassert>
#include <vector>
using namespace std;

class MyCalendarTwo {
public:
    MyCalendarTwo() {
         // Maintain a vector of bookings
    	// Each time we book , check for potential overlaps and if so
    	// add to the overlap map, which is essentailly sorted by start, then by end
    	// If at any point we find something in the overlap, then we need to return false
    	// else add to bookings (and possibly overlap)
    	// It is guaranteed that bookings will have overlaps but will never have more htan one overlap, else we
    	// have failed
    	// overlaps will never have more than one tuple which start from same start time
    	// We know something is overlapped, when previousEnd > currentStart and currentEnd > previousStart 
    	// Min Overlap can be given by max(s0, s1), min(e0, e1)
    }
    
    bool book(int start, int end) {
    	map<int, int> overlaps;
    	auto overlapTwice =[&](pair<int,int> p){
    		auto lp = overlaps.lower_bound(p.first);
    		auto prev = overlaps.end();
    		if (lp != overlaps.begin()) {
    			prev = --lp;
    			lp++;
    		}
    		if ( (prev != overlaps.end() &&
    			prev->second > p.first )) {
    			printf("overlap :%d,%d\n", prev->second, p.first);
    			return true;
    		}
    		if (lp != overlaps.end() &&
    				lp->first < p.second) {
    			  printf("overlap :%d,%d\n", lp->first, p.second);

    			return true;
    		}
    		return false;
    	};

    	auto getOverlap=[](int s0, int e0, int s1, int e1) {
    		return make_pair(max(s0, s1), min(e0, e1));
    	};
    	for (auto& p : bookings) {
    		if (p.second > start && end > p.first) {
    			printf("Curr;%d,%d against :%d,%d\n",p.first, p.second, start, end);
    			auto overlap = getOverlap(p.first, p.second, start, end);
    			if (overlapTwice(overlap)) 
    				return false;
    			else {
    				printf("adding overlap :%d, %d\n", overlap.first, overlap.second);
    				overlaps[overlap.first] = overlap.second;
    			}
    		}
    	}
    	cout << "overlaps size " << overlaps.size() << endl;
     	bookings.push_back(make_pair(start, end));
     	return true;

    }
 	vector<pair<int,int>> bookings;
};


int main() {

	MyCalendarTwo calendar2;
	assert(calendar2.book(10, 20) == true);
 	assert(calendar2.book(10, 40) == true);
 	assert(!calendar2.book(15, 30));

 	MyCalendarTwo calendar22;
 	assert(calendar22.book(47, 50));
 	assert(calendar22.book(1, 10));
 	assert(calendar22.book(27, 36));
 	assert(calendar22.book(40, 47));
 	assert(calendar22.book(20, 27));
 	assert(calendar22.book(15, 23));
 	assert(calendar22.book(10, 18));
}