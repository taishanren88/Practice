#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

    // Find pivot index - assume that there is a pivot point in this array
    // If middle < number directly to left, return the pivot point
    // If the middle number > the start, pivot must be on the right 4,7,0
    // If the middle number < the start, the pivot must be on the left 4,1,2,3
    int findPivot(vector<int>& nums, int start, int end)
    {
        cout << "start is " << start << "end is " << end <<endl;
        int mid = (start + end) / 2;
        if ((end - start < 2))
            return -1;
        else if (nums[mid] < nums[mid-1])
            return mid;
        else
        {

            if (nums[mid] > nums[start]) // increasing, search right
                return findPivot(nums, mid, end);    
             else if (nums[mid] == nums[start]) // try both sides
             {
                 int tryLeft = findPivot(nums, start, mid); 
                if (tryLeft != -1)
                    return tryLeft;
                 else
                    return findPivot(nums, mid, end);
               }         
            else
                return findPivot(nums, start, mid);
        }
    }
    bool findTarget(vector<int>& nums, int target, int start, int end)
    {
        if (start == end)
            return false;
        int mid = (start + end) / 2;
        if (target == nums[mid])
            return true;
        else if (target < nums[mid])
            return findTarget(nums, target, start, mid);
        else
            return findTarget(nums, target, mid +1, end);
    }
    bool search(vector<int>& nums, int target) {
        // Find pivot index
        // If we have a pivot index, search both sides
        const int end = nums.size();
        printf("HERE\n");
        int pivotIndex = findPivot(nums, 0, end);
                printf("HERE2\n");

        if (pivotIndex == -1) // no pivot - do normal binary search
        {
            return findTarget(nums, target, 0, end);
        }
        else
        {
            return findTarget(nums, target, pivotIndex, end) || findTarget(nums, target, 0, pivotIndex);
        }
        
    }
    
    int main()
    {
          vector<int> test = {1,3};
          // assert(search(test, 0) == false);
          // test = {2,5,6,0,0,1,2};
          // assert(search(test,3) == false);
          //  test = {1,1,1,3,1};
          //  assert(findPivot(test, 0, test.size()) == 4);
          //  assert(search(test, 3));

          //  test = {1,1};
          // cout << findPivot(test, 0, test.size());
          //  assert(findPivot(test, 0, test.size()) == -1);
           
          //  test = {2,5,6,0,0,1,2};
          //   assert(search(test, 3) == false);
            
          //   test = {4,5,6,7,0,1,2};
          //  assert(findPivot(test, 0, test.size()) == 4);

           test = {1,2,0,1,1,1};
            assert(findPivot(test, 0, test.size()) == 2);

    }
