#include "common.h"
using namespace std;
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> results = {-1,-1};
        unordered_map <int, int>values;
        for (int i = 0; i < nums.size() ;i++)
            values[nums[i]] = i;
        for (int i = 0; i < nums.size() ; i++)
        {
            int diff = target - nums[i];
            if (diff != nums[i])
            {
                auto itr = values.find((target - nums[i]));
                if (itr != values.end())
                {
                    results[0] = i;
                    results[1] = itr->second;
                    break;
                }
            }
        }
        return results;
    }
    
    int main()
    {
        vector<int> test = {3,2,4};
        auto res  = twoSum(test, 6);
        cout << res[0] <<"," << res[1];
    }
