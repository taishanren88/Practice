#include <iostream>
#include <queue>
using namespace std;

const int WALL = -1;
const int GATE = 0;
void updateIfValid(int i, int j , int m , int n , int currentDistance, vector<vector<int>>&rooms, queue<pair<int, int>>& todo) {
	if ( i >= 0 && i < m && j >= 0 && j < n && 
		rooms[i][j] != WALL && ( (currentDistance + 1) < rooms[i][j]) ) {
		rooms[i][j]  = currentDistance + 1;
		todo.push(make_pair(i, j));
	}
}


void wallsAndGates(vector<vector<int>>& rooms) {
	// Iterate over the entire vector
	// Add all the walls into the queue
	// Do a BFS from our queue in all 4 diretions
	// If target element is not a wall nor a gate, set its value = min(currValue, currValue  + 1)
	//
	//

	queue<pair<int, int>> todo;
	for (int i = 0; i < rooms.size(); i++) {
		for (int j = 0; j < rooms[i].size(); j++) {
			if (rooms[i][j] == GATE) {
				todo.push(make_pair(i, j));
			}
		}
	}
	const int M = rooms.size();
	const int N = rooms[0].size();
	while (!todo.empty()) {
		auto front = todo.front();
		todo.pop();
		auto currVal = rooms[front.first][front.second];
		updateIfValid(front.first - 1, front.second, M, N, rooms[front.first][front.second], rooms, todo);
		updateIfValid(front.first, front.second - 1, M, N, rooms[front.first][front.second], rooms, todo);
		updateIfValid(front.first , front.second + 1, M, N, rooms[front.first][front.second], rooms, todo);
		updateIfValid(front.first + 1, front.second, M, N, rooms[front.first][front.second], rooms, todo);
	}
}

int main () {
	vector<vector<int>> board = {{2147483647, -1, 0, 2147483647}, {2147483647, 2147483647, 2147483647, -1}, {2147483647, -1, 2147483647, -1}, {0, -1, 2147483647, 2147483647}};
	wallsAndGates(board);
	for (int i = 0 ; i < board.size(); i ++) {
		for (int j = 0; j < board[i].size(); j++) {
			cout << board[i][j] << ",";
		}
		cout << endl;
	}
}