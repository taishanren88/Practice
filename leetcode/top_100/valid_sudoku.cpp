
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
bool isValidSudoku(vector<vector<char>>& board) {
// Iterate in blocks of 9 at a time
// Examine rows, columsn, and groups independently
// To easily examine subgroups, maintain a rowgroup index 
// and a column group index
// Column Index advances each sub group
// and row index advances after 3 subgroups
	int rowGroupIndex =0;
	int rowIndex  = 0;
	int columnIndex = 0;

	for (int i = 0; i < 9; i++) {
		unordered_set<char> row;
		unordered_set<char> column;
		unordered_set<char> subgroup;
		for (int j = 0; j < 9; j++ ) {
			auto rowVal = board[i][j];
			auto colVal = board[j][i];

			int subGroupRow = rowIndex + j / 3;
			int subGroupCol = columnIndex + j % 3;
			auto subgroupVal = board[subGroupRow][subGroupCol];

			if (subgroup.find(subgroupVal) != subgroup.end()) {
				return false;
			}
			if (row.find(rowVal) != row.end()) {
				return false;
			}
			if (column.find(colVal) != column.end()) {
				return false;
			}
	
			if (rowVal != '.') {
				row.insert(rowVal);
			}
			if (colVal != '.') {
				column.insert(colVal);
			}
			if (subgroupVal != '.') {
				subgroup.insert(subgroupVal);
			}
		}
		columnIndex = (columnIndex + 3) % 9 ;
		if (columnIndex == 0) {
			rowIndex += 3;
		}
	}
	return true;

}

int main () {
	vector<vector<char>> test1 = {
  {'5','3','.','.','7','.','.','.','.'},
  {'6','.','.','1','9','5','.','.','.'},
  {'.','9','8','.','.','.','.','6','.'},
  {'8','.','.','.','6','.','.','.','3'},
  {'4','.','.','8','.','3','.','.','1'},
  {'7','.','.','.','2','.','.','.','6'},
  {'.','6','.','.','.','.','2','8','.'},
  {'.','.','.','4','1','9','.','.','5'},
  {'.','.','.','.','8','.','.','7','9'}
};
	assert(isValidSudoku(test1) == true);
	vector<vector<char>> test2 = {
  {'8','3','.','.','7','.','.','.','.'},
  {'6','.','.','1','9','5','.','.','.'},
  {'.','9','8','.','.','.','.','6','.'},
  {'8','.','.','.','6','.','.','.','3'},
  {'4','.','.','8','.','3','.','.','1'},
  {'7','.','.','.','2','.','.','.','6'},
  {'.','6','.','.','.','.','2','8','.'},
  {'.','.','.','4','1','9','.','.','5'},
  {'.','.','.','.','8','.','.','7','9'}
};
	assert(isValidSudoku(test2) == false);


}