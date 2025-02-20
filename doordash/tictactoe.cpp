#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
public:
    /** Initialize your data structure here. */
    TicTacToe(int aN)
    :n(aN) {
        rows = vector<vector<int>>(2, vector<int>(n, 0));
        columns = vector<vector<int>>(2, vector<int>(n, 0));
        leftDiagonal = vector<int>(2, 0);
        rightDiagonal =  vector<int>(2, 0);
    }
    
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        // Maintain a vector for rows
        // Maintain a vector for columns
        // Maintain a "left diagonal" value
        // Maintain a "right diagonal" value 
        
        // Update rows and vectors accordingly
        // Update diagonals (ld (row , col) == same or rd (row + col) == n-1)
        auto player_index = 0;
        if (player == 2) {
            player_index = 1;
        }
        rows[player_index][row]++;
        columns[player_index][col]++;

        {
            // update diagonal
            if (row == col) {
                leftDiagonal[player_index]++;
            }
            if (row + col == n -1) {
                rightDiagonal[player_index]++;
            }
        }
        auto checkWin=[this](int& value) {
            return value == n;
        };
        if (checkWin(rows[player_index][row])) return player;
        if (checkWin(columns[player_index][col])) return player;

        if (checkWin(leftDiagonal[player_index])) return player;
        if (checkWin(rightDiagonal[player_index])) return player;


        return 0;
    }
    
    vector<vector<int> > rows;
    vector<vector<int> > columns;
    const int n;
    vector<int> leftDiagonal;
    vector<int> rightDiagonal;
    
};

int main() {
    TicTacToe toe(3);
    assert(!toe.move(0, 0, 1));
    assert(!toe.move(0, 2, 2));
    assert(!toe.move(2,2,1));
    assert(!toe.move(1,1,2));
    assert(!toe.move(2, 0, 1));
    assert(toe.move(2,1,1) == 1);

    TicTacToe toe2(2);
    assert(!toe2.move(0,0,2));
    assert(!toe2.move(1, 1, 1));
    assert(toe2.move(0, 1, 2) == 2);


    TicTacToe toe3(2);
    assert(!toe3.move(0,1,2));
    assert(!toe3.move(1, 0, 1));
    assert(toe3.move(1, 1, 2));

}