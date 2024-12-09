#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

bool isValidSudoku(vector<vector<char>>& board) {
    // Check rows and columns at the same time
    // maintain row vector to mark visited row entries
    // maintain column vector to mark visited column entries
    // maintain group vector to mark group entries
    int groupRow = 0;
    int groupColumn = 0;

    for (int i = 0; i < 9; i++) {
        unordered_set<char> row;
        unordered_set<char> group;
        unordered_set<char> column;
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.' && row.find(board[i][j]) != row.end()) {
                return false;
            }
            row.insert(board[i][j]);
            if (board[j][i] != '.' && column.find(board[j][i]) != column.end()){
                return false;
            }
            column.insert(board[j][i]);
            int currentGroupRow = groupRow + j/ 3;
            int currentGroupColumn = groupColumn + j % 3;
            if (board[currentGroupRow][currentGroupColumn] != '.'
                    && group.find(board[currentGroupRow][currentGroupColumn]) != group.end()){
                return false;
            }
            group.insert(board[currentGroupRow][currentGroupColumn]);
            // printf("(%d,%d)\n", currentGroupRow, currentGroupColumn);
        }
        // printf("####\n");
        groupColumn += 3;
        if (groupColumn == 9) {
            groupColumn = 0;
            groupRow += 3;
        }
    }
    return true;
}

int main() {
    vector<vector<char>> board = {
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
    assert(isValidSudoku(board));
    board = {
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
assert(!isValidSudoku(board));
}