#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int subarraySum(vector<int>& nums, int k) {
    // Want to find is sum (i,j)  == k , inclusive, where sum(0,j) - sum(0,i) == k
    // simplifies to a 2-sum problem, where we want to keep track of counts
    // If sumj - sumI == K, then it means our count is added by count (sumI)
    unordered_map<int, int> sums2Counts;
    sums2Counts[0] = 1;
    int sumJ = 0;
    int total = 0;
    for (auto& num : nums) {
        sumJ += num;
        auto remaining = sumJ - k;
        if (sums2Counts.find(remaining) != sums2Counts.end()) {
            total += sums2Counts[remaining];
        }

        if (sums2Counts.find(sumJ) != sums2Counts.end()) {
            sums2Counts[sumJ] ++;
        }
        else {
            sums2Counts[sumJ] = 1;
        }
    }
    return total;
}

int main() {
    vector<int> nums = { 1, 1, 1};
    assert(subarraySum(nums, 2) == 2);
}