#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

    // find the index where we pivot [4,7,0] , [4,7,0,1]
    int findPivotIndex(const vector<int>& nums, int start,int end)
    {
        int med =( start + end) / 2;
        if (med == 0 || nums[med] <= nums[med - 1]) // At the end pivot must be here or current <= one before
            return med;
        else if ( nums[med] < nums[start]) //middle < start, pivot is to the left 
            return findPivotIndex(nums, start, med);        
        else // search right, the left is increasing
            return findPivotIndex(nums, med, end);
    }
    int findTarget(const vector<int>& nums, int target, int start, int end)
    {
        if (start == end)
            return -1;
        int med = (start + end) / 2;
        if (target == nums[med])
            return med;
        else if (target > nums[med])
            return findTarget(nums, target, med +1, end);
        else
            return findTarget(nums, target, start, med);
            
    }
    // find the target after finding the pivot 
    // find the range where it fits and search tehre
    // find the target after finding the pivot 
    // find the range where it fits and search tehre
    int search(vector<int>& nums, int target) {
        const int end = nums.size();
        if (nums.empty())
            return -1;
        
        if (nums[0] <= nums.back()) // increasing array 100%, no pivot index
            return findTarget(nums, target, 0, end);
        else
        {
            const int pivotIndex = findPivotIndex(nums, 0, end);
            printf("PIVOT INDEX : %d\n", pivotIndex);
            if (target >= nums[pivotIndex] && target <= nums[end-1])
                return findTarget(nums, target, pivotIndex, end);
            else
                return findTarget(nums, target, 0, pivotIndex);
        }
    }
    
int main()
{
    vector<int> test = {1,3};
    assert(search(test, 0) == -1);
    test = {3,1};
    assert(search(test, 1) == 1);
}
