#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int largestRectangleArea(vector<int>& heights) {
    // Maintain a queue of stack of non-decreasing (increasing or larger) heights
    // Iterate over heights array. At each point, if the current element is < top,
    // compute all the areas of previous heights (left ends) to the current point (right end)
    // Right end is exactly this point
    // Left is the point right before the examined height. If there is no left-point, use 0
    stack<int> nonDecreasingHeights; // actually holds indices
    int maxArea = 0;
    int right = 0;
    auto computeArea = [&]() {
         while (!nonDecreasingHeights.empty()
            && heights[right] < heights[nonDecreasingHeights.top()]) {
            auto currentIndex  = nonDecreasingHeights.top();
            auto currentHeight = heights[currentIndex];
            nonDecreasingHeights.pop();
            auto width = nonDecreasingHeights.empty() ? right - 0  : (right - nonDecreasingHeights.top() - 1);
            auto area =  width * currentHeight;
            maxArea = max(maxArea, area);
        }
    };
    for (; right < heights.size(); right++) {
        computeArea();
        nonDecreasingHeights.push(right);
    }
    
    heights.push_back(-1); // sentinel to trigger computeArea function
    computeArea();
    return maxArea;

}

int main() {
    vector<int> heights = {2,1,5,6,2,3};
    assert(largestRectangleArea(heights) == 10);
    heights = {2,1,2};
    assert(largestRectangleArea(heights) == 3);
    heights = {5,4,1,2};
    assert(largestRectangleArea(heights)== 8);
    heights = {0,3,2,5};
   assert(largestRectangleArea(heights) == 6);
}