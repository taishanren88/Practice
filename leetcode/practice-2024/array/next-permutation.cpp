#include <iostream>
#include <vector>
using namespace std;

void nextPermutation(vector<int>& nums) {
	// GO from the back of the array
// find the first number arr[j] > arr[j-1] (e.g. 1,3, 5, 4)
	// e..g 5  (everything to the right is increasing going from <---)
// go to the right again and then find the smallest integer > arr[j-1] and then swap them : [1,4,5,3]
// and ensure we are increasing going from right ot left, then just reverse at the end to get the smallest [1,4,3,5]
	for (int j = nums.size() - 1 ; j > 0 ; j-- ) {
		if (nums[j] > nums[j-1]) {
			int k = nums.size() - 1; 
			while (nums[k] <= nums[j-1]) {
				k --;
			}
			swap(nums[k], nums[j-1]);
			std::reverse(nums.begin() +j, nums.end());
			return;
		}
	}
	std::reverse(nums.begin(), nums.end());
}

int main() {

}