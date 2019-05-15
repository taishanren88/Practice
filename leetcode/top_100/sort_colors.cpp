#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void sortColors(vector<int>& nums) {
    // first place to put zeroes
    int posZeroes = 0;
     // first place to put twos
    int posTwos = nums.size() - 1;
    int indexValueUnknown = 0; // Unsure what thi is
    // Ones wlil come naturally
    // Guaranteed that posZeroes -1 and posTwos + 1 is filled with 0s and 2s respectively
    // Guaranteed that indexValueUnknown >= posZeroes
    while (indexValueUnknown < nums.size() && indexValueUnknown <= posTwos)
    {
        if (nums[indexValueUnknown]  == 0) {
            swap(nums[indexValueUnknown], nums[posZeroes]);
            posZeroes++;
            indexValueUnknown++; // don't care about ones

        }
        else if (nums[indexValueUnknown] == 2) {
            swap(nums[indexValueUnknown], nums[posTwos]);
            posTwos--;
        }
        else {
            indexValueUnknown++; // don't care about ones
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
}