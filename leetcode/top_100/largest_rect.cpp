#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;

/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
*/
int largestRectangleArea(vector<int>& heights) {
	// Maintain a stack of "contiguous", nondecreasing heights
	// For a given point on stack ,everything below current index serves as a left bound for rectangle area
	// If current element is smaller than previous heights , then
	// compute the rectangle of all previous heights (for each rectangle) to this point
	// push current element on, at each point

	stack<int> nondecreasingHeights;
	int maxArea = 0;
	auto computeArea =[&] (int rightBound) {
		auto currentHeight = heights[rightBound];
		while (!nondecreasingHeights.empty()
					&& currentHeight < heights[nondecreasingHeights.top()])
			{
				auto previousHeightLoc = nondecreasingHeights.top();
				auto previousHeight = heights[previousHeightLoc];
				nondecreasingHeights.pop();

				// compute width by considering left bound
				int width = nondecreasingHeights.empty() ? rightBound - 0 : rightBound - nondecreasingHeights.top() - 1;
				maxArea = max(previousHeight * width, maxArea);
			}
	};

	for (int i = 0; i < heights.size(); i++)
	{
		auto currentHeight = heights[i];
		computeArea(i);
		nondecreasingHeights.push(i);
	}

	int originalSize = heights.size();
	heights.push_back(0); // sentinel for the last piece
	computeArea(originalSize);
	return maxArea;
}

int main() {
	vector<int> vec = {2,1,5,6,2,3};
	assert(largestRectangleArea(vec) == 10);
		vec = {2,1,2};
	assert(largestRectangleArea(vec) == 3);
	vec = {3,6,5,7,4,8,1,0};
	assert(largestRectangleArea(vec) == 20) ;
	vec = {4,2,0,3,2,5};
	assert(largestRectangleArea(vec) == 6) ;



}