#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
	// Sort the array
	// Iterate over the array
	// Fix the element at the current pos
	// // Tkae two pointers from left and right
	// take the sum of all 3 // If a + b + c == 0
	// we want b + c == 0
	// if b + c < 0 , increment b, otherwise , decrement c
	// if equal then you have to increment both b and decrement c
	// at each point, we need to make sure we don't do the same for i 
	// 
	// 
	// [ -4, -1, -1, 0, 1, 2]
	// -4 + -1 + 2 = 3 
	// -4 + -1 + 1 = -4
	// -1 + -1 + 2 = 0 (good)
	// 
	// 
	sort(nums.begin(), nums.end(), [](int a, int b) {
		return a < b;
	});
	vector<vector<int>> results;
	for (int i = 0; i < nums.size(); i++) {
		int a = nums[i];
		if (i > 0 && a == nums[i-1]) {
			continue;
		}
		int bIndex = i +1;
		int cIndex = nums.size() - 1;
		while (bIndex < cIndex) {
			auto b = nums[bIndex];
			auto c = nums[cIndex];
			auto sum = a + b + c;
			if (sum == 0) {
				results.push_back({a,b,c});
				bIndex++;
				cIndex--;
				while (bIndex <= cIndex 
						&& nums[bIndex] == nums[bIndex-1]) {
					bIndex++;
				}
				while (bIndex <= cIndex 
					&& nums[cIndex] == nums[cIndex+1])
					cIndex--;
			} else if (sum < 0 ) {
				bIndex++;
			} else {
				cIndex--;
			}
		}

	}
	return results;
}

int main() {

    vector<int> nums = {-1, 1 , 0};
    auto res = threeSum(nums);

    assert(res.size() == 1 && res== vector<vector<int> > ( {{-1, 0, 1}}));

    nums = {5,1,  3, 0,-1};
     res = threeSum(nums);
    assert(res.size() == 1 && res== vector<vector<int> > ( {{-1, 0, 1}}));

    
     nums = {2,-1,  3, 0,-1};
     res = threeSum(nums);
    assert(res.size() == 1 && res== vector<vector<int> > ( {{-1, -1, 2}}));

     nums = {2,-1,  3, 0,-1 , - 1, 2, -1, -1 };
     res = threeSum(nums);
     // for (auto n : res) {
     //    printf("%d, %d,%d...", n[0], n[1], n[2]);
     // }
    assert(res.size() == 1 && res== vector<vector<int> > ( {{-1, -1, 2}}));

    nums = {-1,0,1,2,-1,-4};
     res = threeSum(nums);
     //    for (auto n : res) {
     //    printf("%d, %d,%d...", n[0], n[1], n[2]);
     // }
     assert(res.size() == 2 );
}
