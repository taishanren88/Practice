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
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    // Returns the row/column section for this coordinate
    pair<int,int> getRowSection(int r, int c) const
    {
        return make_pair(r /3, c /3);
    }
    bool isValid(const vector<vector<char>>& board, char value, const int r, const int c)
    {
        auto section = getRowSection(r, c);
        const int sectionRowStart = section.first * 3;
        const int sectionColStart = section.second * 3;
        // Check 3x3 grid
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[sectionRowStart + i][sectionColStart + j] == value)
                    return false;
            }
        }
        // Check vertically
        for (int i = 0; i < 9; i++)
        {
            if (board[i][c] == value)
                return false;
        }
        // Check horizontally
        for (int j = 0; j < 9; j++)
        {
            if (board[r][j] == value)
                return false;
        }
        return true;
    }

    void print(const vector<vector<char>>& board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (auto c : board[i])
                cout << c << ',';
            cout << endl;
        }
    }

    bool helper(vector<vector<char>>& board, int r, int c)
    {
        int i = r;
        int j = c;
        for (; i < 9; i++)
        {
            for (; j < 9; j++)
            {
                if (board[i][j] == '.')
                {
                    bool placed = false;
                    for (char entry = '1'; entry <= '9'; entry++)
                    {
                        if (isValid(board, entry, i , j))
                        {
                            board[i][j] = entry;
                            placed = true;
                            if (!helper(board, i, j + 1))
                            {
                                board[i][j] = '.';
                                placed = false;
                            }
                        }
                    }
                    // nothing placed
                    if (!placed) {
                        // print(board);
                        return false;
                    }
                }
            }
            j = 0;
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
};


int main()
{
    vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'},
                                  {'6','.','.','1','9','5','.','.','.'},
                                  {'.','9','8','.','.','.','.','6','.'},
                                  {'8','.','.','.','6','.','.','.','3'},
                                  {'4','.','.','8','.','3','.','.','1'},
                                  {'7','.','.','.','2','.','.','.','6'},
                                  {'.','6','.','.','.','.','2','8','.'},
                                  {'.','.','.','4','1','9','.','.','5'},
                                  {'.','.','.','.','8','.','.','7','9'}};
    Solution s;
    s.solveSudoku(board);
    s.print(board);
    
    
}