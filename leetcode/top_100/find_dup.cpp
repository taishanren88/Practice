#include <iostream>
#include <vector>

using namespace std;
 int findDuplicate(vector<int>& nums) {
        // We do a binary search of our space , which is 1...n
        // At each level, we count all those that are <= current middle target
        // If we have more , it means we need to shrink the right side to [start, middle]
        // Else If we have <=, it means we need to shrink the left side [mid + 1, end]
        int start = 1;
        int end = nums.size() - 1;
        while (start < end)
        {
            int midtarget = (start + end) /2;
            int lte = 0;
            for (auto n : nums) {
                if (n <= midtarget) 
                    lte++;
            }
            if (lte >  midtarget) {
                end = midtarget; // shrink right
            } else { // have enough on left, shrink left
                start = midtarget + 1;
            }
        }
        return start;
    }

    int main() {
    	vector<int> v = {1,3,4,2,2};
    	cout << findDuplicate(v) << endl;
    	v= {3,1,3,4,2};
    	    	cout << findDuplicate(v) << endl;


    }