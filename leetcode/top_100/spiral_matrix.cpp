#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty())
        return vector<int>();

    vector<int> results;
    int rows = matrix.size();
    int columns = matrix[0].size();
    int topRow = 0;
    int bottomRow = matrix.size() - 1;
    int leftColumn = 0;
    int rightColumn = matrix[0].size() - 1;
    while (topRow <= bottomRow && leftColumn <= rightColumn)
    {
        // Check valid row
        if (topRow <= bottomRow) {
            int j = leftColumn;
            while (j <= rightColumn)
            {
                results.push_back(matrix[topRow][j]);
                j++;
            }
            topRow ++;
        }
        // Check valid column
        if (leftColumn <= rightColumn) {
            int i = topRow;
            while (i <= bottomRow) {
                results.push_back(matrix[i][rightColumn]);
                i++;
            }
            rightColumn--;
        }
        if (topRow <= bottomRow) {
            int j = rightColumn;
            while (j >= leftColumn)
            {
                results.push_back(matrix[bottomRow][j]);
                j--;
            }
            bottomRow--;
        }
        if (leftColumn <= rightColumn) {
            int i = bottomRow;
            while (i >= topRow)
            {
                results.push_back(matrix[i][leftColumn]);
                i--;
            }
            leftColumn++;
        }
    }
     return results;
}

int main() {
	vector<vector<int>> mat1 = {{1,2,3}, {4,5,6}, {7,8,9}};
	assert(spiralOrder(mat1) == vector<int>({1,2,3,6,9,8,7,4,5}));
	vector<vector<int>> mat2 = {{1,2}};
	assert(spiralOrder(mat2) == vector<int>({1,2}));

	vector<vector<int>> mat3 = { {1}, {2}};
	assert(spiralOrder(mat2) == vector<int>({1,2}));

}

