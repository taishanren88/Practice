#include <iostream>
#include <vector>
using namespace std;

 int firstMissingPositive(vector<int>& nums) {
 // 1. Move all of the positive numbers to a reserved portion of the array [0, m]
        // Iterate over arr[0:m]. Looking for a number[1,2,3,...m-1] Maintain: 
        // If num[i] <0 , it means that i + 1 is present
        // If num[i] > 0 , it means i + 1 is missing  (first missing positive)
        // 2. Set arr[abs(num[i]) - 1]  < 0 
        // 3. Iterate over entire array find first index not < 0 or return m + 1
 	int m = 0;
 	for (int i = 0; i < nums.size(); i ++) {
 		if (nums[i] > 0) {
 			nums[m++] = nums[i];
 		}
 	}
 	for (int i = 0; i < m; i++) {
 		auto index = abs(nums[i]) - 1;
 		if (index >= 0 && index < m ) {
 			nums[index] = -1 * abs(nums[index]);
 			for (int j = 0; j < m ; j++){
 				cout << nums[j] << ",";
 			}
 			cout << endl;
 		}
 	}
 	for (int i = 0; i < m; i++){
 		if (nums[i] > 0) {
 			return i + 1;
 		}
 	}
 	return m + 1;
 }

int main() {
	vector<int> nums = {1,2,0};
	cout << firstMissingPositive(nums) << endl;
}