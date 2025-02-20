#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
  // Intuition: Speed can increse for single individual, but efficiency can
  // decrease for that one person and thus for everyone
  // Sort by efficiency, then we'll always know what the "minimum" efficiency is and the
  // additive effect of summing a new speed
  // Maintain a minheap of speeds . If we reached "k", then we can see if adding a new speed will
  // is larger than our min speed. If so, we update our minheap
    vector<pair<int,int>> pairs;
    for (int i = 0; i < efficiency.size() ; i ++) {
        pairs.emplace_back(make_pair(efficiency[i], speed[i]));
    }
    sort(pairs.begin(), pairs.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first > b.first;
    });

    priority_queue<int, vector<int>, greater<int>> minHeap;
    long sumSpeed = 0;
    long result = 0;
    for (auto& p : pairs) {
        if (minHeap.size() < k) {
            minHeap.push(p.second);
            sumSpeed += p.second;
            result = max(result , sumSpeed * p.first);
        } else {
            auto minSpeed = minHeap.top();
            if (p.second > minSpeed) {
                minHeap.pop();
                sumSpeed -= minSpeed;
                minHeap.push(p.second);
                sumSpeed += p.second;
            }
        }
        result = max(result , sumSpeed * p.first);
    }
    return result % ((int) pow(10,9) +7);

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