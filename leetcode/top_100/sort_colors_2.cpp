#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
void sortColors(vector<int>& nums) {
    // Have two pointers, one for unknown, posForZero, and posForTwo
    // If nums[unknown] == 0 , swap with nums[posForZero], increment both unkown and posForZero
    // If nums[unknown] == 2, swap with nums[posForTwo], decrement posForTwo
    // We know that nums[unknown] >= nums[posForZero], if we swap with nums[posForZero] , we can only get a 1
    int posForZero = 0;
    int posUnknown = 0;
    int posForTwo = nums.size() - 1;
    while (posUnknown <= posForTwo) {
        if (nums[posUnknown] == 0) {
            swap(nums[posForZero], nums[posUnknown]);
            posForZero++;
            posUnknown++;
        }  else if (nums[posUnknown] == 2) {
            swap(nums[posUnknown], nums[posForTwo]);
            posForTwo--;
        } else {
            posUnknown++;
        }
    }
    
}

int main() {
    vector<int> nums = {2, 0, 2, 1, 1, 0};
    sortColors(nums);
    assert(nums == vector<int>({0, 0, 1, 1, 2, 2}));

    nums = {2, 0, 1};
    sortColors(nums);
    assert(nums == vector<int>({0, 1, 2}));

    nums = {1,2};
    sortColors(nums);
 
    assert(nums == vector<int>({1,2}));
}