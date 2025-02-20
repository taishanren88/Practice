#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void dfs(vector<vector<int>>& grid, int r, int c, int& maxArea) {
	const int VISITED = -1;
	if (r <0 || r >= grid.size() ||
		c < 0 || c >= grid[r].size()) {
		return;
	}
	if (grid[r][c] == VISITED
		|| grid[r][c] == 0) {
		return;
	}
	maxArea++;
	auto original = grid[r][c];
	grid[r][c] = VISITED;
	//each direction is (r,c)
	vector<pair<int,int>> directions = {{0, -1}, {-1, 0}, {0,1}, {1, 0}};
	for (auto dir : directions) {
		dfs(grid, r + dir.first, c +dir.second, maxArea);
	}
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
	int maxArea = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			int area = 0;
			dfs(grid, i, j , area);
			maxArea = max(area, maxArea);
		} 
	}
	return maxArea;
}

int main() {
	vector<vector<int>> grid ={{0,0,1,0,0,0,0,1,0,0,0,0,0},
 {0,0,0,0,0,0,0,1,1,1,0,0,0},
 {0,1,1,0,1,0,0,0,0,0,0,0,0},
 {0,1,0,0,1,1,0,0,1,0,1,0,0},
 {0,1,0,0,1,1,0,0,1,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,1,1,1,0,0,0},
 {0,0,0,0,0,0,0,1,1,0,0,0,0}};
assert(maxAreaOfIsland(grid) == 6);

grid = {{0,0,0,0,0,0,0,0}};
assert(maxAreaOfIsland(grid) == 0);

}