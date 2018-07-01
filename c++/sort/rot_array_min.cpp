   #include <iostream>
#include <vector>
#include <cassert>
using namespace std;
    tuple<bool,int> findPivotIndex(vector<int>& nums, int start, int end)
    {
        if (end - start < 2)
        {
            printf("HERE\n");
            return make_tuple(false,-1);
        }
        int mid = (end + start) / 2;
       cout <<"mid is " << mid <<endl;

        if (nums[mid] < nums[mid-1])
            return make_tuple(true, mid);
        else if (nums[start] < nums[mid]) // increasing on the left, search the right
           {
               printf("GOIGIN RIGTH\n");
            return findPivotIndex(nums,mid, end);
           }
        else // since start is larger , it means we had a pivot on the left somewhere
            return findPivotIndex(nums,start, mid);
    }
    int findMin(vector<int>& nums) {
        auto tup = findPivotIndex(nums, 0, nums.size());
        cout << get<1>(tup) <<endl;
        if (!get<0>(tup))
            return nums[0];
        else
            return nums[get<1>(tup)];
    }

int main()
{
    vector<int> test = {3,4,5,1,2};
    assert(findMin(test) == 1);
}
