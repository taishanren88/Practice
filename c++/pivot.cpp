/*
Rotated Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.
Your algorithm's runtime complexity must be in the order of O(log n).
*/

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

    int pivotWrapper(const vector<int>& nums, int start, int end)
    {
       //  if (start == end)
       //      return -1;
       //  int mid = (start + end) / 2;
       //  if ((mid + 1 < nums.size()) && nums[mid] > nums[mid + 1])
       //      return mid + 1;
       //  else
       //  {
       //      if (nums[start] < nums[mid])
       //          return pivotWrapper(nums, mid +1, end); 
       //       else
       //          return pivotWrapper(nums, start, mid);
       // }
        int low = 0;
        int high = nums.size() - 1;
        while (low < high)
        {
            int mid = (low + high) /2;
            if (nums[mid] > nums[high])
                low = mid + 1;
            else
                high = mid;
        }
        if (nums[low-1] > nums[low] || nums[low])
            return low;
        else
            return -1;
    }

    int findTarget(const vector<int>& nums, int start, int end, int target)
    {
        if (start == end)
            return -1;
        int mid = (start + end ) /2;
        if (nums[mid] == target) return mid;
        else if (target > nums[mid]) return findTarget(nums, mid +1, end, target);
        else  return findTarget(nums, start, mid, target);
    }
    int search(const vector<int>& nums, int target) {
       auto pivot= pivotWrapper(nums, 0, nums.size());
        if (pivot != -1)
        {
            cout << pivot << endl;
            auto found = findTarget(nums, 0, pivot, target);
            if (found == -1) 
                return findTarget(nums, pivot, nums.size(), target);
            else
                return found;
        }
        else 
            return findTarget(nums, 0, nums.size(), target);
    }

int main()
{
    cout << search({3,1}, 3);
    assert(search({3,1}, 3) == 0);
    cout << search({5,1,3}, 5);
     cout << search({6,7,8,1,2,3,4,5}, 6);
}
