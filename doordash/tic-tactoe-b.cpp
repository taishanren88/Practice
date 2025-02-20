#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
public:
    /** Initialize your data structure here. */
    TicTacToe(int aN)
    :n(aN) {
        row = vector<vector<int>>(2, vector<int>(n, 0));
        col = vector<vector<int>>(2, vector<int>(n, 0));
        leftDiagonal = vector<int>(2, 0);
        rightDiagonal = vector<int>(2, 0);
    }
    
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */

    int move(int r, int c, int player) {
        int playerIndex = 0;
        if (player == 2) {
            playerIndex = 1;
        }

        row[playerIndex][r]++;
        col[playerIndex][c]++;
        if (r == c) {
            leftDiagonal[playerIndex]++;
        }
        if (r + c == n -1) {
            rightDiagonal[playerIndex]++;
        }
        auto checkWin = [&]() {
            if (row[playerIndex][r] == n
                || col[playerIndex][c] == n
                || leftDiagonal[playerIndex] == n
                || rightDiagonal[playerIndex] == n) {
                return true;
            }
            return false;
        };
 
        if(checkWin()) {
            return player;
        } else {
            return 0;
        }

    }
private:
    vector<vector<int>> row;
    vector<vector<int>> col;
    vector<int> leftDiagonal;
    vector<int> rightDiagonal;
    int n;
};

int main() {
    TicTacToe toe(3);
    assert(!toe.move(0, 0, 1));
    assert(!toe.move(0, 2, 2));
    assert(!toe.move(2,2,1));
    assert(!toe.move(1,1,2));
    assert(!toe.move(2,0,1));
    assert(toe.move(2,1,1) == 1);

}
