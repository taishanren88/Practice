#include <iostream>

#include <vector>
#include <stack>
using namespace std;  
   int largestRectangleArea(vector<int>& heights) {
        stack<int> increasing; // Increasing heights (index stored, not value)
        int maxArea = 0;
        auto modifyMax =[&increasing, &maxArea, &heights] (int right, bool force)
        {
             while (!increasing.empty() && ( (heights[increasing.top()] > heights[right]) ||force))
             {
                auto frontIndex = increasing.top();
                increasing.pop();
                maxArea = max( (right - frontIndex) * heights[frontIndex], maxArea);
             }
            if (!increasing.empty())
                cout << "top befoer push is " << heights[increasing.top()] << endl;
            increasing.push(right);
            cout << "push right " << right << "currently size " << increasing.size() << endl;
        };

        int originalSize = heights.size();
        heights.push_back(0);
        for (int i = 0; i < originalSize; i++)
        {
            modifyMax(i, false);
        }
        modifyMax(originalSize, false);
        return maxArea;
    }

int main()
{
    vector<int> v = {2,1,2};
    cout << largestRectangleArea(v);

}
