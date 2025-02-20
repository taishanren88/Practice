#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<int>>& rooms, int r, int c, int current) {
	if (r < 0 || r >= rooms.size() || c < 0 || c >= rooms[r].size() || rooms[r][c] != 0 && rooms[r][c] <= current) {
		return;
	}

	rooms[r][c] = current;
	dfs(rooms, r + 1, c, current + 1);
	dfs(rooms, r - 1, c, current + 1);
	dfs(rooms, r , c -1 , current + 1);
	dfs(rooms, r , c +1 , current + 1);

}

void wallsAndGates(vector<vector<int>>& rooms) {
	// Do a DFS from each gate
	// If the element is not a gate nor an obstacle, set its minimum value
	for (int i = 0; i < rooms.size(); i++){
		for (int j = 0; j < rooms[i].size(); j++) {
			if (rooms[i][j] == 0) {
					dfs(rooms, i, j, 0);
			}
		}
	}
	return;
}
int main() {

}