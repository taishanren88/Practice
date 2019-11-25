#include <iostream>
#include <vector>
using namespace std;
    void eliminateDfs(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[i].size())
            return;
        if (board[i][j] == 'O') {
            board[i][j] = 'I';
            eliminateDfs(board, i+1, j);
            eliminateDfs(board, i -1, j);
            eliminateDfs(board, i , j -1);
            eliminateDfs(board, i , j + 1);
        }
        else 
            return;
    }
    void solve(vector<vector<char>>& board) {
        // Eliminate border points that are 'O' and their adjacent values
        // Change them to some arbitrary value
        // Change rest to 'X'
        // Change arbitrary value back to 'O'
        if (board.empty())
            return;
        for (int j = 0; j < board[0].size(); j++)
        {
            auto lastRow = board.size() - 1;
            if (board[0][j] == 'O')
                eliminateDfs(board, 0, j);
            if (board[lastRow][j] == 'O')
                eliminateDfs(board, lastRow, j);
        }
        for (int i = 0; i < board.size(); i++)
        {
            if (board[i][0] == 'O')
                eliminateDfs(board, i, 0);
            auto lastCol = board[i].size()-1;
            if (board[i][lastCol] == 'O')
                eliminateDfs(board, i , lastCol);
        }
        auto change =[&](char from, char to ) {
             for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[i].size(); j++)
                {
                    if (board[i][j] == from)
                        board[i][j] = to;
                }
            }
        };
        change('O', 'X');
        change('I', 'O');
    }

    int main() {
        vector<vector<char>> v = {{'O','O','O'},{'O','O','O'},{'O','O','O'}};
        solve(v);
        for (int i = 0; i < v.size() ; i++)
        {
            for (int j = 0; j < v[i].size() ; j++)
                cout << v[i][j] << ",";
            cout << endl;
        }
        v = {
{'O','X','O'},
{'X','O','X'},
{'O','O','O'},
{'O','X','O'}};


       solve(v);
        for (int i = 0; i < v.size() ; i++)
        {
            for (int j = 0; j < v[i].size() ; j++)
                cout << v[i][j] << ",";
            cout << endl;
        }
        v = {{'X','X','X','X'},
{'X','O','O','X'},
{'X','X','O','X'},
{'X','O','X','X'}};
solve(v);
        for (int i = 0; i < v.size() ; i++)
        {
            for (int j = 0; j < v[i].size() ; j++)
                cout << v[i][j] << ",";
            cout << endl;
        }

    }