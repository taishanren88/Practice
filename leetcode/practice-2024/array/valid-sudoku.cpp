#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

bool check(char c, unordered_set<char>& toprocess) {
	if (c == '.') {
		return true;
	}
	if (toprocess.find(c) != toprocess.end()) {
		return false;
	}
	toprocess.insert(c);
	return true;
}
  bool isValidSudoku(vector<vector<char>>& board) {

  	// check rows
  	for (int i = 0; i < 9 ; i ++) {
  		unordered_set<char> row;
  		unordered_set<char> column;
  		for (int j = 0; j < 9; j++){
  			if (!check(board[i][j], row)) {
  				return false;
  			}
  			if (!check(board[j][i],column)) {
  				return false;
  			}
  		}
  	}

  	for (int k = 0; k < 9; k ++) {
  		unordered_set<char> subgrid;
  		for (int i = 0; i < 3; i++) {
  			for (int j = 0; j < 3; j++){
  				auto ii = (k / 3) * 3 + i;
  				auto jj = (k % 3 ) * 3 + j;
  				// cout << ii << ", " << jj << endl;
  				if (!check(board[ii][jj],subgrid)) {
  					return false;
  				}
  			}
  		}
  	}
  	// For each row, check if there are numbers 1- 9
  	// For each column, check if there are numbers 1 - 9 
  	// check each subblock
  	// 
  	return true;
    }

int main(){
vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'}
,{'6','.','.','1','9','5','.','.','.'}
,{'.','9','8','.','.','.','.','6','.'}
,{'8','.','.','.','6','.','.','.','3'}
,{'4','.','.','8','.','3','.','.','1'}
,{'7','.','.','.','2','.','.','.','6'}
,{'.','6','.','.','.','.','2','8','.'}
,{'.','.','.','4','1','9','.','.','5'}
,{'.','.','.','.','8','.','.','7','9'}};
cout << isValidSudoku(board) << endl;

board = {{'8','3','.','.','7','.','.','.','.'}
,{'6','.','.','1','9','5','.','.','.'}
,{'.','9','8','.','.','.','.','6','.'}
,{'8','.','.','.','6','.','.','.','3'}
,{'4','.','.','8','.','3','.','.','1'}
,{'7','.','.','.','2','.','.','.','6'}
,{'.','6','.','.','.','.','2','8','.'}
,{'.','.','.','4','1','9','.','.','5'}
,{'.','.','.','.','8','.','.','7','9'}};
cout << isValidSudoku(board) << endl;
}