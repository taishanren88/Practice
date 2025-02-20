#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
	vector<pair<int, int>> dirs =
	{
		make_pair(0, -1),
		make_pair(0, 1),
		make_pair(-1, 0),
		make_pair(1, 0),
		make_pair(-1, -1),
		make_pair(1, -1),
		make_pair(1, 1),
		make_pair(-1, 1),
	};
	// Use BFS on the entire grid starting from the top-left
	// if we reach (m-1) , (n-1), we are done
	// at each point of the BFS , set visited grid to -1 (mark as visited)
	int total_len = 0;
	queue<pair<int, int>> todo;
	todo.push(make_pair(0, 0));
	if (grid[0][0] != 0) {
		return -1;
	}
	const auto N = grid.size();
	while (!todo.empty()) {
		auto len = todo.size();
		total_len++;
		for (int i = 0; i < len; i++) {
			auto front = todo.front();
			todo.pop();
			// printf("%d, %d\n", front.first, front.second);
			if (front.first ==  N - 1 && front.second == N-1
			        && grid[N - 1][N - 1] == 0) {
				return total_len;
			}
			grid[front.first][front.second] = -1;
			for (auto& dir_pair : dirs) {
				auto next_i = front.first + dir_pair.first;
				auto next_j = front.second + dir_pair.second;
				if (next_i >= 0 && next_i < grid.size()
				        && next_j < grid[next_i].size()
				        && next_j >= 0
				        && grid[next_i][next_j] != -1
				        && grid[next_i][next_j] == 0) {
					todo.push(make_pair(next_i, next_j));
				}
			}
		}
	}
	return -1;
}

int main() {
	vector<vector<int>> grid = {{0, 1}, {1, 0}};
	cout << shortestPathBinaryMatrix(grid) << endl;

	vector<vector<int>> grid2 = {{0,0,0},{1,1,0},{1,1,0}};
	cout << shortestPathBinaryMatrix(grid2) << endl;
}