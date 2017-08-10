#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

/*
Given a sorted array consisting of only integers where every element appears twice except for one element which appears once. Find this single element that appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10
Note: Your solution should run in O(log n) time and O(1) space.
*/
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
    	// Assume, based on the nature of the problem , we always have at least three elements
    	return singleNonDuplicateWorker(nums, 0, nums.size());

    }
    int singleNonDuplicateWorker(vector<int>& nums, int start, int end)
    {
    	if ((end - start) <= 1)
    		return nums[start];
    	int middle = (end + start) /2;

    	if (middle % 2 == 0) // even compare middle integer to integer on left, since we may be last element and not have anything to the right
    	{
			if (nums[middle] == nums[middle - 1])
				return singleNonDuplicateWorker(nums, start, middle);
			else
				return singleNonDuplicateWorker(nums, middle, end);
   		}
   		else // odd compare middle integer to integer on teh right
   		{
			if (nums[middle] == nums[middle + 1])
				return singleNonDuplicateWorker(nums, start, middle);
			else
				return singleNonDuplicateWorker(nums, middle, end);
   		}

		return true;
    }
};

int main()
{
	Solution s;
	vector<int> v = {1, 2, 2};
	vector<int> v2= {1, 1, 2};
	assert(s.singleNonDuplicate(v) == 1);
	assert(s.singleNonDuplicate(v2) == 2);
	vector<int> v3 = {1,1,2,3,3};
	assert(s.singleNonDuplicate(v3) == 2);
	vector<int> v4 = {3,3,7,7,10,11,11};
	assert(s.singleNonDuplicate(v4) == 10);


}