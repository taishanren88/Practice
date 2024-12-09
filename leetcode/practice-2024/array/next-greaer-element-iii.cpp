#include <iostream>
#include <stdexcept>      // std::invalid_argument

using namespace std;

    int nextGreaterElement(int n) {
	auto nums = std::to_string(n);
	// Iterate from right to left.
	// Find the first integer which is > than the integer on the left
	// Up to this point, it means everythign was increasing <---
	// Once you find that value, loop again from right to left to find the first smallest
	// value > than the  integer on left. Swap them.
	// // Now we just want to minimzie the increasing sequence going from <---, so reverse tthem

	for (int i = nums.size() - 1; i >= 1; i--) {
		if (nums[i] > nums[i - 1]) {
			int j = nums.size() - 1;
			while (j > i) {
				if (nums[j] > nums[i - 1]) {
					break;
				}
				j--;
			}
			swap(nums[i - 1], nums[j]);
              for (int l = 0 ; l < nums.size() ; l++ ){
                cout << (nums[l]) << ", ";
            }
            reverse(nums.begin() + i, nums.end());
      
      		auto converted = stol(nums);
            if (converted >= INT_MAX) {
            	return -1;
            } else{
            	return converted;
            }
		}
	}
    return -1;

	

}

int main() {

}