#include <iostream>
#include <vector>

using namespace std;

static const int EMPTY = 0;
static const int OBSTACLE = -1;
static const int START = 1;
 static const int END = 2;

void dfs(vector<vector<int> >& grid, int row, int col, const int destRow,const  int destCol, int count, const int requiredCount, int& result) {
    static const int VISITED = -2;
    
    if (row < 0 || row >= grid.size() 
        || col < 0 || col >= grid[row].size()
        || grid[row][col] == VISITED || grid[row][col] == OBSTACLE) {
        return;
    }
    else if (row == destRow 
            && col == destCol) {
         if (count == requiredCount) {
	        result++;
    	}
        return;
    }

	auto original= grid[row][col];
    grid[row][col] = VISITED;
    dfs(grid, row + 1, col, destRow, destCol, count + 1, requiredCount, result);
    dfs(grid, row -1, col, destRow, destCol, count + 1, requiredCount, result);
    dfs(grid, row , col + 1, destRow, destCol, count + 1, requiredCount, result);
    dfs(grid, row, col - 1, destRow, destCol, count + 1, requiredCount, result);
    grid[row][col] = original;
}
int uniquePathsIII(vector<vector<int> >& grid) {
    // Find start/end. Count # of squares we need
    // IF we reach start/end with exact # of squares we are done, otherwise return false
    int required = 0;
    int startRow, startCol;
    int endRow, endCol;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == EMPTY || grid[i][j] == START) {
                required++;
            } 
            if (grid[i][j ] == START) {
                startRow = i;
                startCol = j;
            } else if (grid[i][j] == END) {
                endRow = i;
                endCol = j;
            }
        }
    }
    int result = 0;
    dfs(grid, startRow, startCol, endRow, endCol, 0, required, result);
    return result;
}

int main() {
	vector<vector<int> > grid = {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
	auto result = uniquePathsIII(grid);
	assert(result == 2);
	grid = {{0,1},{2,0}};
	result = uniquePathsIII(grid);
	assert(result == 0);
	grid = {{1,0,0,0},{0,0,0,0},{0,0,0,2}};
	result = uniquePathsIII(grid);
	assert(result == 4);
}