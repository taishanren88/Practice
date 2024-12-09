#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
using namespace std;

/*
 *Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.



Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

*/
vector<int> twoSum(vector<int>& nums, int target) {
	// Iterate over teh vector. We want a + b  = targt
	// We know target. So for every a, there's a possibility that there could be some b that a + b = target
	// SO just note a and its position and if you find (target - b ) = a existing, we are good
	// // Just store all "a", and then then find some b such that target -b = a

	unordered_map<int,int> found;
	for (int i = 0; i < nums.size(); i++ ) {
		auto foundOther = found.find(target - nums[i]);
		if (foundOther != found.end()) {
			return vector<int>({found[target - nums[i]], i});
		}
		found[nums[i]] = i;
	}
std::cout << "shouldn't be hre" << endl;
return {};
}

int main() {
	auto vec = std::vector<int>({2,7,11,15});
	auto result =  twoSum(vec, 9);
		cout << result[0] << "," <<  result[1] << endl;
}