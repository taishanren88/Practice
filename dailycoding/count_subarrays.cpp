#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

bool validMapping(const vector<bool>& mapping, int pos)
{
    for (int i = 0; i <= pos; i++)
    {
        if (!mapping[i])
            return false;
    }

    return true;
}
int countSubarraysBruteForce(vector<int> input){
    
    vector<bool> mapping (input.size(), false);
    int count = 0;
    for (int i = 0; i < input.size(); i++)
    {
        mapping[input[i]] = true;

        if (validMapping(mapping, i))
        {
            count++;
        }
    }

    return count;
}


int countSubarrays(vector<int> input) {
    int runningSum = 0;
    int count = 0;
    for (int i = 0; i < input.size(); i++)
    {
        runningSum += input[i];
        int maxSumToInclude = i * (i+1) / 2;
        if (runningSum == maxSumToInclude)
            count++;
    }

    assert(countSubarraysBruteForce(input) == count);
    return count;
}

int main()
{
    
    assert(countSubarrays({4,3,2,1,0}) == 1);
    assert(countSubarrays({0,1,2,3,4}) == 5);
    assert(countSubarrays({2,1,0,3,4}) == 3);
}