#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

 void dfs(vector<vector<int>>& grid, int i, int j, int val, int& maxCount) {
	if (i < 0 || i >= grid.size() || j <0 || j >= grid[i].size()) {
		return;
	}
	if (grid[i][j]  == 0 || grid[i][j]  > 1) {
		return;
	}
	if (grid[i][j] == 1) {
		grid[i][j] = val;
		maxCount++;
	}
	dfs(grid, i -1, j, val, maxCount);
	 dfs(grid, i +1, j, val, maxCount);
	dfs(grid, i, j-1, val, maxCount);
	dfs(grid, i, j+1, val, maxCount);

}

int getIslandIndex(int i , int j, vector<vector<int>>& grid, unordered_map<int,int>& islandSizes)  {
	if (i < 0 || i >= grid.size() || j <0 || j >= grid[i].size()) {
		return 0;
	}
	return grid[i][j];
}

int largestIsland(vector<vector<int>>& grid) {
    // Iterate over each element 
    // Mark each island (on the grid). use a unique number (aka index)
    // Update the max island size
    // also store the island's size in map[index] -> size
    
    // At the very end, if the current element is water, 
    // get the total size of neighboring unique islands and add them together
    
    int index = 2;
    int result = 0;
    unordered_map<int, int> islandSizes;
    for (int i = 0; i < grid.size(); i++) {
    	for (int j = 0; j < grid[i].size(); j++){
    		int maxCount = 0 ;
    		dfs(grid, i, j, index, maxCount);
    		if (maxCount > 0 ) {
    			islandSizes[index] = maxCount;
	    		index++;
	    		result = max(result, maxCount);
    		}
    	}
    }
    islandSizes[0] = 0; // sentinel
    for (int i = 0; i < grid.size(); i++) { 
    	for (int j = 0; j < grid[i].size(); j++) {
    		if (grid[i][j] == 0 ){
    			   unordered_map<int,int> neighbors;
    			auto one = getIslandIndex( i-1, j, grid, islandSizes);
    			neighbors[one] = islandSizes[one];
    			auto two = getIslandIndex( i+1, j, grid, islandSizes);
    			 neighbors[two] = islandSizes[two];
    			auto three = getIslandIndex( i, j-1, grid, islandSizes);
    			 neighbors[three] = islandSizes[three];
    			auto four = getIslandIndex( i, j+1, grid, islandSizes);
    			 neighbors[four] = islandSizes[four];
    			 int current = 1;
    			 for (auto& kv : neighbors) {
    			 	current += kv.second;
    			 	// printf("here with :%d,%d\n", kv.first, kv.second);
    			 }
    			 // printf("Done\n");
    			 result = max(result, current);
    		}
    	}
    }

    return result;
}
int main() {
	 vector<vector<int>> grid = {{1,0}, {0,1}};
	 largestIsland(grid);
	// for (int i = 0; i < grid.size(); i++) {
	// 	for (int j = 0; j < grid[i].size();j++) {
	// 		printf("grid[i][j]: %d,", grid[i][j]);
	// 	}
	// 	printf("\n");
	// }

}