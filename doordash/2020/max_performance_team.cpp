#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
    // Intuition 1: Though efficiency can decrease with additional members, 
    // sum of speeds can increase total efficiency
    // Intuition 2: If we sort by decreasing effiiency, 
    // we can keep a running maximum calculation of performance, and eliminate those
    // where a new minimum efficiency * total speed reduces maximum calculated so far
    // Maintain a minheap of speeds where you remove old speeds, which are no longer used
    vector<pair<int,int>> pairs;
    for (int i = 0; i < efficiency.size(); i++) {
    	pairs.emplace_back(make_pair(efficiency[i], speed[i]));
    }
    sort(pairs.begin(), pairs.end() , [] (const pair<int,int> &a, const pair<int,int>& b) {
    	return a.first > b.first;
    });
    priority_queue<int, vector<int>, std::greater<int> > minHeap;
    long sumSpeed = 0;
    long totalEffiency = 0;
    for (auto& p : pairs ) {
    	if (minHeap.size() == k) {
    		if (minHeap.top() < p.second) {
	    		sumSpeed -= minHeap.top();
	    		minHeap.pop();
	    		minHeap.push(p.second);
	    		sumSpeed += p.second;
    		}
    	} else {
    		minHeap.push(p.second);
    		sumSpeed += p.second;
    	}
    	totalEffiency = max(totalEffiency, sumSpeed * p.first);
    }
    return totalEffiency%((int)pow(10,9) + 7);
}

int main() {
	vector<int> speed = { 2, 10, 3, 1, 5, 8};
	vector<int> efficiency = {5,4,3,9,7,2};
    vector<pair<int,int>> pairs;
    for (int i = 0; i < efficiency.size(); i++) {
    	pairs.emplace_back(make_pair(efficiency[i], speed[i]));
    }
    sort(pairs.begin(), pairs.end() , [] (const pair<int,int> &a, const pair<int,int>& b) {
    	return a.first > b.first;
    });
    // For debug print only, to get intuition behind the problem
	for (int i = 0; i < pairs.size(); i++) {
		cout << pairs[i].first << ' ';
	}
	cout << endl;
	for (int i = 0; i < pairs.size(); i++) {
		cout << pairs[i].second << ' ';
	}
	cout << endl;
	cout << maxPerformance(speed.size(), speed, efficiency, 2)  << endl;
	assert(maxPerformance(speed.size(), speed, efficiency, 2) == 60);

	// MH  = 1, 	SS = 1, => 9
	// MH = 1, 5 ,  SS= 6, => 42
	// MH = 2, 5,  SS = 7 => 35
	// MH = 5, 10, SS = 15  => 60
	// MH = 8, 10, SS = 20 => 40
}