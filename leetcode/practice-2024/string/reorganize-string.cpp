#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

string reorganizeString(string s) {
	unordered_map<char, int> charCounts;
	for (int i = 0; i < s.size(); i++){
		charCounts[s[i]]++;
	}
	// create a max heap of characters with their character counts
	// while the heap is not empty
	// pop off the heap
	// append the charater to the string
	// if heap is empty and char counts is empty -- we are done. return result
	// pop off again
	// decrement count and append to string
    // return empty at the bottom
	// This comparator will be used to build minheap.
	auto cmp = [&](char a, char b) {
	    return charCounts[a] < charCounts[b];
	};
	using MaxHeap = priority_queue<char, vector<char>, decltype(cmp)> ;
	MaxHeap maxHeap(cmp);

	for (auto kv : charCounts ) {
		maxHeap.push(kv.first);
	}
	string result;
	while (!maxHeap.empty()) {
		auto front1 = maxHeap.top();
		maxHeap.pop();

		result += front1;
		charCounts[front1]--;
		if (maxHeap.empty()){
			if (charCounts[front1] == 0) {
				break;
			} else {
				return "" ;
			}
		}
	
		auto front2=  maxHeap.top();
		maxHeap.pop();
		result += front2;
		charCounts[front2]--;
		if (charCounts[front1] > 0 ) {
			maxHeap.push(front1);
		}

		if (charCounts[front2] >0) {
			maxHeap.push(front2);
		}
	}
    return result;
}

int main() {
	cout << reorganizeString("aab") <<endl;
		cout << reorganizeString("abba") <<endl;
	cout << reorganizeString("aaab") <<endl;

}