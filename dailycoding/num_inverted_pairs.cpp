#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int mergeAndCount(vector<int>& nums, int start, int mid, int end)
{
    int pos = start;
    vector<int> left (nums.begin() + start, nums.begin() + mid + 1);
    vector<int> right(nums.begin() + mid + 1, nums.begin() + end + 1);

    int i = 0;
    int j = 0;
    int numInverted = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            nums[pos++] = left[i];
            i++;
        }
        else
        {
            // Everything in left arrayis sorted, so however many elements are remaining is count of inverted
            numInverted += left.size() - i;
            nums[pos++] = right[j];
            j++;
        }
    }
    while(i < left.size())
    {
        nums[pos++] = left[i];
        i++;
    }
    while (j < right.size())
    {
        nums[pos++] = right[j];
        j++;
    }
    
    return numInverted;
}

int mergeSortWrapper(vector<int>& nums, int start, int end)
{
     if (start >= end)
        return 0;

    int mid = (start + end) / 2;
    int leftCount = mergeSortWrapper(nums, start, mid);
    int rightCount = mergeSortWrapper(nums, mid + 1, end);
    return mergeAndCount(nums, start, mid, end) + leftCount + rightCount;
}

int reversePairs(vector<int>& nums) 
{
    return mergeSortWrapper(nums, 0, nums.size() - 1);
}

int main()
{
    vector<int> nums = {2, 4, 1, 3, 5};
    assert(reversePairs(nums)  == 3);
    nums ={5, 4, 3, 2, 1};
    assert(reversePairs(nums)  == 10);
}