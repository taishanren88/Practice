#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

int findKthLargest(vector<int>& nums, int k) {
	// Create a min heap of size k.
	// Loop through the original array.
	// At any point if the currente lement is > than the minHeap's top element, evict from teh minheap
	// At the end just pop until the last element
	using MinHeap =     std::priority_queue<int, std::vector<int>, std::greater<int> >;

	MinHeap minHeap;
	for (auto& n : nums) {
		if (minHeap.size() < k) {
			minHeap.push(n);
		} else {
			if (minHeap.top() < n) {
				minHeap.pop();
				minHeap.push(n);
			}
		}
	}
	int last = minHeap.top();
	return last;

}

int main() {
	vector<int> vec = {3, 2, 1, 5, 6, 4};
	assert(findKthLargest(vec, 2) == 5);
	vec = {3, 2, 3, 1, 2, 4, 5, 5, 6};
	assert(findKthLargest(vec, 4) == 4);
}