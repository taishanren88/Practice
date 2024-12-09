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

/**
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
*/
int getPreviousCost(vector<vector<int>>& grid, int r, int c) {
	int cost = 0;
	int prevRow = r- 1;
	if (prevRow >= 0 && prevRow < grid.size()) {
		cost += grid[prevRow][c];
	}
	int prevCol = c- 1;
	if (prevCol >=0 && prevCol < grid[r].size()) {
		cost += grid[r][prevCol];
	}
	return cost;
}
int uniquePaths(int m, int n) {
    // At any point, we can go right or down, which means at any cell we arrived from left or
    // from above.
 	// Assume that there's one possible path starting at (0,0). Add up the cost from left and above
 	// at every point
 	vector<vector<int>> grid(m, vector<int>(n, 0));
 	for (int j = 0; j < n ; grid[0].size(), j++) {
 		grid[0][j] = 1;
 	}

 	for (int i = 1; i < m; i++ ){
 		for (int j = 0; j < n ; j++) {
 			grid[i][j] = getPreviousCost(grid, i, j);
 		}
 	}
 	return grid[m-1][n-1];
}

int main() {
	assert(uniquePaths(3, 2) ==  3);
	assert(uniquePaths(7, 3) == 28);

}