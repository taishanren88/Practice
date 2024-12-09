#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    // maintain a maxheap of the index with a custom comparator of using the tempreature value
    // while current temperature is > top, subtract indices and update results
    
	 auto cmp =[&](int a, int b ) {
		return temperatures[a] < temperatures[b];
	};
    stack<int> decreasingTemperatures;
    vector<int> results(temperatures.size(), 0);
    for (int i = 0; i < temperatures.size(); i++){
    	while (!decreasingTemperatures.empty() 
    		&& temperatures[i] > temperatures[decreasingTemperatures.top()]) {
    		results[decreasingTemperatures.top()] = i - decreasingTemperatures.top();
    		decreasingTemperatures.pop();
    	}
    	decreasingTemperatures.push(i);
    }
    return results;
}

int main() {
	// auto cmp =[](int a, int b ) {
	// 	return a < b;
	// };
 //    priority_queue<int, vector<int>, decltype(cmp)> maxHeap(cmp);
 //    maxHeap.push(1);
 //    maxHeap.push(3);
 //    maxHeap.push(2);
 //    cout << maxHeap.top() << endl;
	vector<int> temperatures = {73,74,75,71,69,72,76,73};
	auto res =	dailyTemperatures(temperatures);
	for (int j = 0 ; j < res.size() ;j++){
		cout << res[j]<<  ",";
	}
    
}