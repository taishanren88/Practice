#include <iostream>
#include <vector>
using namespace std;

void nextPermutation(vector<int>& nums) {
    // Look from the right. Find the first digit which is > than the number on its left ( call it target)
    // It is the case that those to the right of this point are all increasing , when viewing from left
    // Now loop again and find the first one on the right which is also < than the target
    // reverse everything to the right of target now to minimiez the increase
    int j = nums.size() - 1;
    while (j >= 1 ) {
        if (nums[j] > nums[j-1]) {
            auto target = j -1;
            int k = nums.size() - 1; 
            while (k > target ) {
                if (nums[k] > nums[target]) {
                    swap(nums[k], nums[target]);
                    reverse(nums.begin() + j, nums.end());
                    return;
                }
                k--;
            }
        }
        j--;
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

    nums = {2, 3, 1};
    nextPermutation(nums);
    assert(nums[0] == 3 && nums[1] == 1
            && nums[2] == 2);
}