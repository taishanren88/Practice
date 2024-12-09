#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> getOrder(vector<vector<int>>& tasks) {
    // Sort tasks by enqueue time
    // Keep track of the current time , so that we know when we can enqueue tasks
    // at each point, check to see if we can add more tasks(enqueue_i <= T) to our minheap , if so do it.
    // If we finish our queue, then maybe we finished too early, if so reset our time
    //
    //
   for (int i = 0; i < tasks.size(); i++){
    	tasks[i].push_back(i);
    }
    sort(tasks.begin(), tasks.end());

	 auto cmp = [](const vector<int>& a, const vector<int>& b) { 
	 return a[1] > b[1]; }; // For min-heap
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

    auto t = 0;
    int i = 0;
    vector<int> results;

    while (i < tasks.size() || !pq.empty()) {
    	while (i < tasks.size() && t >=  tasks[i][0]) {
    			pq.push(tasks[i]);
				i++;
		}
    	if (!pq.empty()) {
    		auto front = pq.top();
    		pq.pop();
    		results.push_back(front[2]);
    		t += front[1];
    	} else {
    		if (i < tasks.size() && t < tasks[i][0]) {
    			t = tasks[i][0];
    		}
    	}
    }


    return results; 
}

int main() {
	vector<vector<int>> tasks = {{1,2},{2,4},{3,2}, {4,1}};
	auto res = getOrder(tasks);
	for ( int i = 0; i < res.size(); i ++) {
		cout << res[i] << ",";
	}

}