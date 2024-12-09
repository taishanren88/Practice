#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& nums, int target) {
    // If nums[start] < nums[mid], It could not have rotated here . only search the left if target is >= nums[start] and target <= nums[mid]. Else search right
    // if nums[start] > nums[mid], it means it rotated on the left.  If target is > nums[mid] && target is < nums[start] , search the right , else search the left
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end ) {
        int mid = (start + end) / 2;
        int midVal = nums[mid];
        printf (" %d, %d -> %d\n", start, end, midVal);
        if (target == midVal) {
            return mid;
        }
        if (nums[start] <= midVal) {
            if (target >= nums[start] 
            		&& target <= midVal) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        } else {
            if (target > nums[mid]
            	&& target < nums[start]) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
    }
    return -1;
}

int main () {
	vector<int> v = {4,5,6,7,0,1,2};
	assert(search(v, 0) == 4);
	assert(search(v, 3) == -1);
	v = {1};
	assert(search(v,0) == -1);


	v = {1};
	assert(search(v,0) == -1);

	v = {1,3};
	assert(search(v,3) == 1);


	v = {5,1,3};
	assert(search(v,5) == 0);


	v = {5,1,2,3,4};
	assert(search(v,1) == 1);
}