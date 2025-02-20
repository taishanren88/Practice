#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <locale>
#include <iomanip>
#include <map>
#include <set>
#include <unordered_map>


using namespace std;

class Scooter {
    
    public :
    Scooter() {
        
    }
    bool book(int start, int end) {
        auto after = bookings.upper_bound(start); //
        auto before = after;
    
        if (before != bookings.begin()) {
            // find first booking which has a start time <= current start time
            before--;
        }
        
        auto detectOverlap = [&](pair<int,int>& a, pair<int,int>& b){
            if (b.first < a.first) {
                swap(a,b);
            }
            if (a.second >= b.first) {
                return true;
            } else
                return false;
        };
        
        auto now = make_pair(start, end);
        if (before != bookings.end()) {
            int beforeStart = before->first;
            int beforeEnd = before->second;
            auto beforeP = make_pair(beforeStart, beforeEnd);
            if (detectOverlap(now, beforeP))
                return false;
        }
        if (after != bookings.end()) {
            int afterStart = after->first;
            int afterEnd = after->second;
            auto afterPair = make_pair(afterStart, afterEnd);
            if (detectOverlap(now, afterPair))
                return false;
        }
        
        bookings[now.first] = bookings[now.second];
        return false;
        
    }
    
private:
    map<int, int> bookings;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
