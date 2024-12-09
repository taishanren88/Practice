#include <iostream>
#include <stack>
#include <vector>
using namespace std;
   int largestRectangleArea(vector<int>& heights) {
        // The maximal area of any height is its right bound * left bound * height
        // To find the right bound, find the first element, which is smaller than its height
        // To find the left bound, find the first element to the left which is smmaller than it. If nothing is smaller, this is the smallest , use -1 as the left bound
        // Use a stack to keep track of non-decreasing heights. if we find a height smaller than top, compute all of the areas, for which height is smaller >=. right bound is this point exactly. left bound is one to the left or -1.
        stack <int> mystack;
        int maxArea = 0;
        auto computeArea =[&](int right) {
            while (!mystack.empty()
                   && heights[mystack.top()] > heights[right]) {
                auto top = mystack.top();
                mystack.pop();
                int left = mystack.empty() ? -1 : mystack.top();
                int area = heights[top] * (right - left -1);
                maxArea = max(area, maxArea);
                // printf("(%d,%d) -> %d\n", left, right, area);
            }
            mystack.push(right);
        };
        
        heights.push_back(0);  // sentinel to evalute height for those that are stilll lying at the very end
        for (int i = 0; i < heights.size(); i++ ){
           computeArea(i);
        }
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