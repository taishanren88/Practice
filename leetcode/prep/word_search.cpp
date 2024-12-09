#include <iostream>
#include <vector>
using namespace std;

bool dfs(vector<vector<char>>& board, string word, int index, int r, int c) {
	// Check if pos == word.size() , if so return true
	// Check if r, c is valid. If not , return false
	// Check if board[r][c] has been checked. If so, return false
	// Otherwise mark this one as visited
	// Check if board[r][c] == word[index],  If so, then then keep going , else stop and reutrn false
	constexpr char VISITED = '\0';
	if (index == word.size()) {
		return true;
	}
	if (r < 0 || r >= board.size() ||
		c< 0 || c >= board[r].size()) {
		return false;
	}
	if (board[r][c] == VISITED) {
		return false;
	}
	auto original = board[r][c];
 	if (board[r][c] == word[index]) {
 		board[r][c] = VISITED;
		if (dfs(board, word, index + 1, r, c + 1)
			|| dfs(board, word, index + 1, r, c - 1) 
			|| dfs(board, word, index + 1, r + 1 , c )
			|| dfs (board,word, index + 1, r -1, c)) {
			return true;
		}
	}
	 // restore
	board[r][c] = original;
	return false;

}
bool exist(vector<vector<char>>& board, string word) {
	for (int r = 0;  r < board.size(); r ++) {
		for (int c = 0; c < board[r].size(); c++) {
			if (board[r][c] == word[0]) {
				if (dfs(board, word, 0, r, c)) {
					return true;
				}
			}
		}
	}
	return false;
}


int main() {
	vector<vector<char>>board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
	auto original = board;
	assert(exist(board, "ABCCED"));
	board = original;
	assert(exist(board, "SEE"));
	board = original;
	assert(!exist(board, "ABCB"));
}