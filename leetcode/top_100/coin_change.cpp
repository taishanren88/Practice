#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int coinChange(vector<int>& coins, int amount) {
     /**
    *
    if (dp(prevCost) + cost[j] == sumAmount) {
        dp(currCost) = dp(prevCost) + 1;
    } else {
        dp(currCost) = Impossible
    }
    */
    // Create an array of cost, reflecting min # of coins to reach a target amount
    // This array has indices from [0,amt]
    // Initialize dp[0] to be 0
    // at any point minimum of current cost against prevCost (if it exists ) + 1
    vector<long> dp(amount + 1, -1);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++ ) { 
        for (int j = 0; j < coins.size(); j++) {
            int coinValue = coins[j];
            if (i - coinValue >= 0
            	&& dp[i-coinValue] != -1) {
            	if (dp[i] == -1) {
               		dp[i] = dp[i-coinValue] + 1;
            	} else {
               		dp[i] = min (dp[i], dp[i-coinValue] + 1);
            	}
            }
        }
    }
    return dp[amount];
}

int main()  {
	vector<int> arr = {1,2,5};
	assert(coinChange(arr,11) == 3);
	arr = {2};
	assert(coinChange(arr,3) == -1);

}