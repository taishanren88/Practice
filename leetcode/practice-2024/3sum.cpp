#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
// Sort the vector
// Iterate over the array
// For each:
// Fix the current element:num[i].
// Find some num[j] + num[k] + num[i] = 0 or num[j] + num[k] = -num[i],
// where j < k and j > i

	vector<vector<int>> results;
	std::sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); i++) {
		if (i > 0 && nums[i] == nums[i-1] ) {
			continue;
		}
		auto target = -nums[i];
		int j = i + 1;
		int k = nums.size() - 1;
		while (j < k) {
			auto currSum = nums[j] + nums[k];
			if (currSum ==target) {
				results.push_back(vector<int>{nums[i], nums[j], nums[k]});
				j++;
				k--;
				while (j < k && nums[j] == nums[j-1]){
					j++;
				}
				while (j < k && nums[k] == nums[k+1]){
					k--;
				}
			}
			 else if (currSum < target) {
			 	j++;
			 } else {
			 	k--;
			 }
		}
	}

	return results;
}
int main() {
	vector<int> nums = {-1,0,1,2,-1,-4};
	auto res = threeSum(nums);
	for (int i = 0; i< res.size(); i++){
		cout << "{ " << res[i][0] <<" , " << res[i][1] << " , " << res[i][2] << " }, ";
	}


}