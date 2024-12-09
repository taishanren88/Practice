#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

string reorganizeString(string S) {
    // Create a mapping of characters to counts
    // Create a maxheap storing the letters and their counts
    // For each iteration, pop 2 items
    // Case 1. Only 1 item and count is > 1, return ""
    // Case 2. Append current character, decrement count of both and addd back to the string
	unordered_map<char, int> charCounts;
	for (auto c : S ) {
		if (charCounts.find(c) == charCounts.end()) {
			charCounts[c] = 1;
		} else {
			charCounts[c]++;
		}
	}
	auto compare = [&charCounts](char a, char b) { return charCounts[a] < charCounts[b]; };
	std::priority_queue<char, std::vector<char>, decltype(compare)> maxHeap(compare);
	for (auto& kv : charCounts) {
		maxHeap.push(kv.first);
	}
	std::string result;
	while (!maxHeap.empty()){
		auto front1 = maxHeap.top();
		maxHeap.pop();
		result += front1;
		charCounts[front1]--;
		if (maxHeap.empty()) {
			if (charCounts[front1] > 0) {
				return "";
			} else {
				break;
			}
		}
		auto front2= maxHeap.top();
		maxHeap.pop();
		result += front2;
		charCounts[front2]--;
		if (charCounts[front1] > 0) {
			maxHeap.push(front1);
		}
		if (charCounts[front2] > 0 ) {
			maxHeap.push(front2);
		}
	}
    return result;
}

int main() {

	assert(reorganizeString("aab") == "aba");
	assert(reorganizeString("aaab") == "");
	assert(reorganizeString("cb")  == "bc");


}