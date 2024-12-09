#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// passed string objects length
struct VectorHasher
{
  size_t
  operator()(const vector<int> & obj) const
  {
    return obj[0] ^ obj[1] ^ obj[2];
  }
};

struct VectorComparator
{
  bool
  operator()(const vector<int> & obj1, const vector<int> & obj2) const
  {

    return obj1[0] == obj2[0] 
            && obj1[1] == obj2[1] 
            && obj2[2] == obj2[2];
  }
};


void twoSum(vector<int>& nums, int ignoreIndex, unordered_set<vector<int> , VectorHasher, VectorComparator>& results, unordered_map<long, vector<int>> & mapping) {
    long target = -nums[ignoreIndex];

    for (int i = 0; i < nums.size(); i++)
    {
        if (ignoreIndex != i) {
            long remaining = target - nums[i];
            auto foundItr = mapping.find(remaining);
            if (foundItr != mapping.end()
                 && (foundItr->second[0] != i  && 
                    foundItr->second[0] != ignoreIndex)
                    ) {
                vector<int> a;
                a.push_back(nums[ignoreIndex]);
                a.push_back((int)remaining);
                a.push_back(nums[i]);
                sort(a.begin(), a.end());

                results.insert(a);
            }
        }
    }

}

vector<vector<int>> threeSum(vector<int>& nums) {
    // Sort the input array
    // Consider a single element at a time
    // Do a standard bi-directional search for 2-sum
    // To avoid duplicates at the beginning, ensure the 
    // first element is not the same as the adjacent element, which wsa searched
    // For the the other 2-elements do a 2-sum search
        // Goal find numbers b + c = -a
        // Fix a, find two number b + c = -a
        // Sort the input, skip adjacent duplicates
        // Loop through while (i < j )
        // if sum is too small, increment i, else if sum is too large , increment j
        // If equal, then advance i,j until  they are no longer the same
        if (nums.empty()) 
            return vector<vector<int>>();
        sort(nums.begin(), nums.end());
        vector<vector<int>> results;
        for (int i = 0 ; i < (nums.size() - 2); i++) {
            cout << "SHOULD NOT BE HERE ";
            if (i > 0 && nums[i] == nums[i-1])
                continue;
            int j = i + 1;
            int k = nums.size() - 1;
            int target = -nums[i];
            while (j < k ) {
                int sum = nums[j] + nums[k];
                if (sum < target)
                    j++;
                else if (sum > target)
                    k --;
                else {
                    vector<int> tmp;
                    tmp.push_back(nums[i]);
                    tmp.push_back(nums[j]);
                    tmp.push_back(nums[k]);
                    results.push_back(tmp);
                    j++;
                    k--;

                    while (j < k && nums[j] == nums[j-1])
                        j++;
                    while (j < k && nums[k] == nums[k+1])
                        k--;
                }
            }
        }
        return results;
}

int main() {
    vector<int> input = {-1, 0, 1, 2, -1, -4};
  auto res =  threeSum(input);
  for (auto& v : res) {
    for( auto c : v) {
        cout << c << ",";
    }
    cout << endl;
  }
  // input = {0, 0};
  // res  = threeSum(input);
  // for (auto& v : res) {
  //   for( auto c : v) {
  //       cout << c << ",";
  //   }
  //   cout << endl;
  // }
}