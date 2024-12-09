#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

int trap(vector<int>& height) {
    // At any point the maximum value you can trap at any point, is the (min(maxLeft, maxRight) - height) * 1
    // maxLeft for any point i , is max[0,i-1]
    // maxRight for any point j , is max[j+1, end]
    vector<int> maxLeft(height.size(), 0);
    vector<int> maxRight(height.size(), 0);
    for (int i = 1; i < height.size();  i ++ ) {
    	maxLeft[i] = max(height[i-1], maxLeft[i-1]);
    }
    for (int j = height.size() - 2;j >=0 ;  j -- ) {
    	maxRight[j] = max(height[j+1], maxRight[j+1]);
    }

    int result = 0;
    for (int i = 0 ; i < height.size(); i++) {
    	int minHeightCaptured = min(maxLeft[i], maxRight[i]);
    	if (minHeightCaptured > height[i]) {
    		result += minHeightCaptured - height[i];
    	}
    }
    return result;

}
int main() {

	vector<int> heights = {0,1,0,2,1,0,1,3,2,1,2,1};
	assert(trap(heights) == 6);
	heights = {2,0,2};
	assert(trap(heights) == 2);
}