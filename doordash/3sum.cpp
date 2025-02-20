#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    // Sort the vector
    // For each element 'a' in sorted array, fix it
    // We want to find b + c == -1
    // Do a 2sum passthroughout the remaining
    // if (b + c == target), advance left  and right pointer until both left and right is different
    sort(nums.begin(), nums.end());
    vector<vector<int> > results;
    for (int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i-1]){
            continue;
        }

        int target = -nums[i];
        int left = i + 1;
        int right = nums.size() - 1;
        while (left < right) {
            auto sum = nums[left] + nums[right];
            if (sum == target) {
                vector<int> result = {nums[i], nums[left], nums[right]};
                results.push_back(result);
                left++;
                while (left < right && nums[left] == nums[left-1]) {
                    left++;
                }
                right--;
                while (right > left && nums[right] == nums[right+1]) {
                    right--;
                }
            } else if (sum < target) {
                left++;
            } else {
               right--;
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