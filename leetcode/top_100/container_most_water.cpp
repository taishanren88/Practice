#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int>& height) {
    // Take a pointer from the left, another form the right
    // Compute the area : min(h1,h2) * distance. Since we want to maximize height, if current height is smaller, advance that pointer
    int left = 0;
    int right = height.size()-1;
    int area = 0;
    while (left < right) {
        int minHeight = min(height[left], height[right]);
        area = max(area, minHeight* (right - left));
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return area;
}


int main() {
	vector<int> heights = {1,8,6,2,5,4,8,3,7};
	assert(maxArea(heights) == 49);
}