#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    // Create a vector of pairs <difficulty,profit>
    // Sort the workers  by diffculty and then by profit
    // Find the maximum profit for this worker 
    // iterate over each worker and take the max of the previous profit and up until the max difficulty
    //  Append to result
     vector<vector<int>> difficultiesAndProfits;
     for (int i = 0 ; i < difficulty.size() ; i++) {
			difficultiesAndProfits.push_back({difficulty[i], profit[i]});
     }

     sort (difficultiesAndProfits.begin(), difficultiesAndProfits.end());
     sort(worker.begin(), worker.end());
     int result = 0;
     int j = 0;
     int maxProfit = 0; 
     for (int i = 0 ; i < worker.size() ; i ++) {
     	// find the hardest job this worker can handle
     	while (j < difficultiesAndProfits.size() && worker[i] >= difficultiesAndProfits[j][0]) {
			maxProfit = std::max(maxProfit, difficultiesAndProfits[j][1]);
     		j++;
     	}
   		result += maxProfit ;
     }
     return result;

}

int main() {
	vector<int> difficulty = {2,4,6,8,10};
	vector<int> profit = {10,20,30,40,50};
	vector<int> worker = {4,5,6,7};
	auto result = maxProfitAssignment(difficulty , profit, worker);
	cout << result << endl;
}