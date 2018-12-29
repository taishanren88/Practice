/*Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.
Example: 
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
Follow up:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n). 
*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

// 1. Calculate the running Sum using, right and left pointer
// 2. If we reach the a sum >= target, reduce elemnets from teh second pointer
// 3. Calculate the minimum
int  minSum(const vector<int>& nums, int S)
{
    int runningSum = 0;
    int minLength = INT_MAX;
    for (int right = 0, left = 0; right < nums.size(); right++)
    {
        runningSum += nums[right];
        if (runningSum >= S)
        {
            while (runningSum - nums[left] >= S)
            {
                runningSum -= nums[left];
                left++;    
            }
            cout << "Right" << right << "left " << left <<endl;
            minLength = min(right - left + 1, minLength);
        }
    }
    if (minLength == INT_MAX)
        return 0;
    else
        return minLength;

}
int main()
{
    cout << minSum({2,3,1,2,4,3}, 7) <<endl;
    assert(minSum({2,3,1,2,4,3}, 7) == 2);
        cout << minSum({2,3,1,2,1,1,1,1, 1, 1, 4,3}, 7) <<endl;
     assert(minSum({2,3,1,2,1,1,1,1, 1, 1, 4,3}, 7) == 2);
     assert(minSum({1,2,3,4,5}, 11) == 3);
     assert(minSum({1,1,5,1,2}, 8) ==3);

}
