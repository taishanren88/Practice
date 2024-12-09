#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

bool dfs(vector<vector<char>>& board, const string word, int stringPos, int row , int col) {

	if (stringPos == word.size()) {
		return true;
	}
	if (row < 0 || row >= board.size()
		|| col < 0 || col >= board[row].size()
		|| board[row][col] == '\0') {
		return false;
	}
    if (board[row][col] == word[stringPos]) {
    	auto originalChar = board[row][col];
    	board[row][col] = '\0';
    	if (dfs(board, word, stringPos + 1, row -1 , col)) {
    		board[row][col] = originalChar;
    		return true;
    	}
    	if (dfs(board, word, stringPos + 1, row +1 , col)) {
    	    board[row][col] = originalChar;
    		return true;
    	}
    	if(dfs(board, word, stringPos + 1, row , col - 1)) {
    		 board[row][col] = originalChar;
    		return true;
    	}
    	if (dfs(board, word, stringPos + 1, row , col + 1)) {
    		board[row][col] = originalChar;
    		return true;
    	}
    	 board[row][col] = originalChar;
    }
    return false;
}

bool exist(vector<vector<char>>& board, string word) {
	 // Loop through every character of the board
	// If it starts with the current letter, do a DFS on it
	// mark things as visited by making the character null
    for (int i = 0; i < board.size(); i++ ){
    	for (int j = 0; j < board[i].size(); j++) {
    		if (board[i][j] == word[0]) {
    			if (dfs(board, word, 0, i ,j)) {
    				return true;
    			}
    		}
    	}
    }
    return false;
}

int main() {
	vector<vector<char>> board = {{'A','B','C','E'},
  {'S','F','C','S'},
  {'A','D','E','E'}};
	assert(exist(board ,"ABCCED"));
	assert(exist(board ,"SEE"));
	assert(!exist(board ,"ABCB"));
}