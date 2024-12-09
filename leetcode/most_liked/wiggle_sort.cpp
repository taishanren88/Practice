#include <iostream>
#include <vector>
using namespace std;

/*324. Wiggle Sort II

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].
Example 2:

Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?
*/

void wiggleSort(vector<int>& nums) {
	// Find the median of the array
	// Once we know median, sort such that all values of the mediann are grouped together, things > are > , and things < are <
	int len = nums.size();
	const int nth = len % 2 == 0 ? len / 2 - 1: len / 2;
	std::nth_element(nums.begin() , nums.begin() + nth, nums.end());
	// for (auto n : nums) {
	// 	printf("%d,", n);
	// }
	// printf("\n");	
    auto median = nums[nth];
    // printf("median :%d\n", median);

	int greaterThan = nums.size() - 1;
	int lessThan = 0;
    int i = 0;
	while (i < greaterThan) {
		if (nums[i] > median) {
			swap(nums[i], nums[greaterThan]);
			greaterThan--;
		} else if (nums[i] < median) {
			swap(nums[i], nums[lessThan]);
			lessThan++;
			i++;
		} else {
			i++;
		}
	}
    
	// for (auto n : nums) {
	// 	printf("%d,", n);
	// }
	// printf("\n");	

	// Take numbers on left side (including median), but start at the median, so it doesn't overlap with medians on the right
	// If even mid is half - 1, else odd it's half
	int mid = nth;

	vector<int> temp = nums;
	for (int i = 0; i < len ; i +=2,mid--) {
		nums[i] = temp[mid];
	}

	// Take numbers on right side so it doesnt overlap
	int right = len - 1;
	for (int i = 1; i < len; i+=2, right--) {
		nums[i] = temp[right];
	}

}

int main() {
	vector<int> v = {1, 5, 1, 1, 6, 4};
	// 1, 1, 1, 4, 5, 6 , [1,1,1], [6, 5]..[4]
	// 1,  6, 1, 5, 1, 4
	// 1,  6, 1, 4, 5, 1
	wiggleSort(v);
	// assert(v == vector<int>({1,6,1,5,1,4}));
	for (auto n : v ) {
		printf("%d,", n);
	}
	printf("\n");

	vector<int> v2 = {1,3,2,2,3,1};
	// 1, 1, 2, 2, ,3 3, [1,1] ...[2] ,[3,3]..[2]
	// 1, 3, 1, 3, 2, 2
	wiggleSort(v2);
	// assert(v2 == vector<int>({2,3,1,3,1,2}));

	for (auto n : v2 ) {
		printf("%d,", n);
	}

	vector<int> v3 = {4,5,5,5,5,6,6,6};
	// [4]..[5,5]..[5]    [ 6, 6, 6]..[5]
	wiggleSort(v3);
		for (auto n : v3) {
		printf("%d,", n);
	}

	// assert(v3 == vector<int>({5,6,5,6,5,6,4,5}));
	printf("\n");
	vector<int> v4 = vector<int>({1,3,2,2,3,1});
		wiggleSort(v4);
		//[1,1]...[2] [3, 3]...[2]
		for (auto n : v4) {
		printf("%d,", n);
	}
	// assert(v4 == vector<int> ({2,3,1,3,1,2}));
	printf("\n");

	vector<int> v5 = vector<int>({4,5,5,5,5,6,6,6});
	wiggleSort(v5);

	for (auto n : v5) {
		printf("%d,", n);
	}
	// assert(v5 == vector<int>({5,6,5,6,5,6,4,5}));

	printf("\n");
	vector<int> v6 = vector<int>({4,5,5,6});
	wiggleSort(v6);

	for (auto n : v6) {
		printf("%d,", n);
	}
	 // assert(v5 == vector<int>({5,6,5,6,5,6,4,5}));

}