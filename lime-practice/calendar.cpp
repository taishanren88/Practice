#include <iostream>
#include <map>
#include <cassert>
using namespace std;

class MyCalendar {
public:
    MyCalendar() {
        
    }

    bool book(int start, int end) {
        // use lower_bound which returns a start time >= current element
        // or invalid if no overlap
        //lower_bound -1, gives the last overlapping on the left
        // lower_bound , gives the first overlapping on the right
        auto itr = times.lower_bound(start);
        std::map<int,int>::iterator  prev = times.end();

        if (itr != times.begin()) {
            itr--;
            prev = itr;
            itr++;
        }
        if ((prev != times.end()  && prev->second > start) || (itr != times.end() && itr->first < end))
            return false;
        times[start] = end;
        if (times.lower_bound(start) != times.end())
        	cout << "good" << endl;
        return true;
        
    }
    map<int, int> times;
};
	

int main () {
	MyCalendar calendar;
	assert(calendar.book(37, 50));
	assert(!calendar.book(33, 50));

	MyCalendar calendar2;
	assert(calendar2.book(10, 20));
	assert(!calendar2.book(15, 25));


}