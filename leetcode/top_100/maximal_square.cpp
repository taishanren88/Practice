#include <iostream>
#include <vector>

using namespace std;
     int helper(vector<vector<char>> & matrix, vector<vector<int>>& dp, int i, int j, int& maxSize)
    {
        if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[i].size())
            return 0;
        if (dp[i][j] == -1)
        {
            if (matrix[i][j] == '0')
                dp[i][j] = 0;
            else 
            {
                int bottom = helper(matrix, dp, i + 1, j, maxSize);
                int right = helper(matrix, dp, i, j +1, maxSize);
                int bottomRight = helper(matrix,dp, i + 1, j +1, maxSize);
                dp[i][j] = min(min(bottom, right), bottomRight) + 1;
                maxSize = max(maxSize, dp[i][j]);
                // printf("(%d,%d) -> %d\n", i, j, dp[i][j]);
             }
        }
        return dp[i][j];
    }
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty())
            return 0;
        // We define "size" as the amount of 1s in same amount of rows and columns
        // Key observation: At any point, the maximum size is the minimum of its right, bottom, and bottom right neighbors
        //	plus 1, if current value is also 1, else it's 0
        // We wil use top down DP-recursion to
        // Visit every point in the matrix, check it's relevant neighbors, and update
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), -1));
        int maxSize = 0;
        for (int i = 0; i < matrix.size(); i ++)
        {
        	for (int j = 0; j < matrix[i].size(); j++)
        		helper(matrix, dp, i, j, maxSize);
        }
        return maxSize * maxSize;
    }
int main() {
	vector<vector<char>> matrix = {{'1','1','1'},
									{'1','1','1'},
									{'1','1','1'}};
	cout << maximalSquare(matrix) << endl;

}