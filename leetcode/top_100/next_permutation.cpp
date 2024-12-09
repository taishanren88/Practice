#include <iostream>
#include <vector>
using namespace std;

void nextPermutation(vector<int>& nums) {
    // Examine number from the right.
    // While the current one is <= to the one on left, keep moving left
    // If we hit a point, where current one is > than one to the left, 
    // Iterate again from the end to the fin the smallest value that is > than this
    // Everything previously to the right of this point was increasing, when going from right to left
    // reverse everything to the right
    for (int i = nums.size() - 1; i >= 1; i--) {
        if (nums[i] > nums[i-1]) {
            int j = nums.size() - 1;
            while (j >= i && 
                  nums[j] <= nums[i-1]) {
                j--;
            }
            swap(nums[j], nums[i-1]);
            reverse(nums.begin() + i , nums.end());
            return;
        }
    }
    reverse(nums.begin(), nums.end());
}

int main() {
	vector<int> nums = { 1,3,2};
	nextPermutation(nums);
	assert(nums[0] == 2 && nums[1] == 1 
			&& nums[2] == 3);

	nums = {1, 2, 3};
	nextPermutation(nums);
	assert(nums[0] == 1 && nums[1] == 3
			&& nums[2] == 2);

	nums = {1, 1, 5};
	nextPermutation(nums);
	assert(nums[0] == 1 && nums[1] == 5
			&& nums[2] == 1);
}