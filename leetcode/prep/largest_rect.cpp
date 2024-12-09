#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int largestRectangleArea(vector<int>& heights) {
    // maintain a stack of non-decreasing heights. if current height is < stack top , compute area
    // of all previous heights
    // Case 1 : area = (right - left - 1) * height (if smaller height below the stack top)
    // Case 2 :  area = (right ) * height (if this is the smallest element)
    stack<int> nonIncreasingHeights;
    int maxArea = 0;

    heights.push_back(0);
    auto computeArea =[&](int current) {
    	const auto height = heights[current];
    	while (!nonIncreasingHeights.empty()
    			&& height < heights[nonIncreasingHeights.top()]) {
    		auto top = nonIncreasingHeights.top();
    		auto previousHeight =heights[top];
    		nonIncreasingHeights.pop();
    		if (nonIncreasingHeights.empty()) {
    			maxArea = max(maxArea, current * previousHeight);
    		} else {
    			maxArea = max(maxArea, (current - nonIncreasingHeights.top() - 1) * previousHeight);
    		}
    	}
    	nonIncreasingHeights.push(current);
    };
    for (int i = 0; i < heights.size(); i++ ){
    	computeArea(i);
    }
    return maxArea;
}

int main() {

	  vector<int> heights = {2,1,5,6,2,3};
   cout << largestRectangleArea(heights) << endl;
    heights = {2,1,2};
    assert(largestRectangleArea(heights) == 3);
    heights = {5,4,1,2};
    assert(largestRectangleArea(heights)== 8);
    heights = {0,3,2,5};
  assert(largestRectangleArea(heights) == 6);
}