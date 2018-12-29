 #include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cassert>

using namespace std;
    void dfs(int row,  int numQueens, vector<string>& board, vector<vector<string>>& oResults);
        bool isValid(int row, int col, vector<string>&board);
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board (n, string(n, '.'));
        vector<vector<string>> results;
        dfs(0, 0, board, results);
        return results;
    }
    void dfs(int row,  int numQueens, vector<string>& board, vector<vector<string>>& oResults)
    {
        const int n = board.size();
        if (row == n)
        {
            // for (string s: board)
            //     cout << s <<endl;
            // cout <<endl << endl;
            if (numQueens == n)
            {
                oResults.push_back(board);
            }
            return;
        }
        // search column of a row
        // take the current row
        // for each column , consider the queen placed there, and not placed there
        // look up and to the left, look up and to the right
        for (int i = 0;i < n; i++)
        {
            if (isValid(row, i, board))
            {
                board[row][i] = 'Q';
                dfs(row + 1, numQueens + 1, board, oResults);
            }
            else
            {
                dfs(row +1, numQueens, board, oResults);
            }
           
            board[row][i] = '.';
        }
    }
    bool isValid(const int row,const int col, vector<string>&board)
    {
        // check to the upper left

        int m = row - 1, n = col -1;
        while (m >= 0 && n>=0)
        {
            if (board[m][n] == 'Q')
                return false;
            m--;
            n--;
        }
 
        m = row -1 ;
        n = col + 1;
        // check to the upper right
        while (m>=0 && n < board.size())
        {
            if (board[m][n] == 'Q')
                return false;
            m--;
            n++;
        }
        m = row-1;
        n = col;
        while (m>=0)
        {
           if (board[m][n] == 'Q')
                return false;
            m--;
        }
        return true;
         // no need to check vertically up (because with each recursive call you guarantee before going down that you can do this)
    }
    
int main()
{
    auto res = solveNQueens(4);
    for (auto& v : res)
    {
        for (string s : v)
            cout <<  s << endl; 
        cout << endl << endl;
    }
}
