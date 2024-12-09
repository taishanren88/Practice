#include <iostream>
#include <vector>
using namespace std; 

int search(vector<int>& nums, int target) {
    // if mid element == target, return true
    int leftIndex = 0;
    int rightIndex = nums.size() - 1;
    while (leftIndex <= rightIndex) {
        int midIndex = (leftIndex + rightIndex) / 2;
        int mid = nums[midIndex];
        int right = nums[rightIndex];
        int left = nums[leftIndex];
        if (target == mid ) {
            return midIndex;
        } else if (left > mid) {
            if (target >= mid && target <= right) {
                leftIndex = midIndex + 1;
            } else {
                rightIndex = midIndex - 1;
            }
        } else { 
            if (target <= mid && target >= left) {
                rightIndex = midIndex - 1;
            } else {
                leftIndex = midIndex + 1;
            }
        }
    }
    return -1;

}

int main() {

vector<int> v = {4,5,6,7,0,1,2};
    assert(search(v, 0) == 4);
     assert(search(v, 3) == -1);
    v = {1};
    assert(search(v,0) == -1);


    v = {1};
    assert(search(v,0) == -1);

    v = {1,3};
    assert(search(v,3) == 1);


    v = {5,1,3};
    assert(search(v,5) == 0);


    v = {5,1,2,3,4};
    assert(search(v,1) == 1);

     v = {5,1,3};
    assert(search(v,3) == 2);
}