#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

 void dfs(vector<vector<int>>& grid,vector<vector<int>>& cache, int i, int j, int previousVal, int previousLength, int& maxValue) {
	if (i < 0 || i >= grid.size() || j <0 || j >= grid[i].size()) {
		return;
	}
	if (grid[i][j] < 0) {
		return ;
	}
	
	if (grid[i][j] > previousVal) {
		int original = grid[i][j];
		grid[i][j] = -1 * grid[i][j];
		// cache[i][j] = previousLength + 1;;
		previousLength = previousLength + 1;
		maxValue = max(maxValue, previousLength + 1);
		dfs(grid, cache, i -1, j, original,  previousLength + 1 ,maxValue);
		dfs(grid, cache, i +1, j,original, previousLength + 1, maxValue);
		dfs(grid, cache, i, j-1, original,  previousLength + 1, maxValue);
		dfs(grid, cache, i, j+1, original,  previousLength + 1, maxValue);
	}
	
}

int longestIncreasingPath(vector<vector<int>>& matrix) {
	int maxResult = 0;
	vector<vector<int>>cache;
    for (int i = 0; i < matrix.size(); i++) {
    	for (int j = 0; j < matrix[i].size(); j++){
    		int localResult = 0;
    		dfs(matrix,cache, i,j,matrix[i][j] ,0, localResult);
    		maxResult = max(maxResult, localResult);
    	}
    }
    return maxResult;
}