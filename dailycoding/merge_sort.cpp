#include <iostream>
#include <vector>
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
            numInverted++;
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

void mergeSortWrapper(vector<int>& nums, int start, int end)
{
     if (start >= end)
        return;

    int mid = (start + end) / 2;
    mergeSortWrapper(nums, start, mid);
    mergeSortWrapper(nums, mid + 1, end);
    mergeAndCount(nums, start, mid, end);

}
void mergeSort(vector<int>& nums)
{
     mergeSortWrapper(nums, 0, nums.size() - 1);
}

int main()
{
    vector<int> nums = {5,4,3,2,1};
    mergeSort(nums);
    for (auto n: nums)
        cout << n << ", ";
}