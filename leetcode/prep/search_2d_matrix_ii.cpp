#include <iostream>
#include <vector>

using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    // start from top right
    // if element is  < current element, search one column to the left
    // if element is > current element, search one row to the bottom
    if (matrix.empty()) {
        return false;
    }
    const int nRows = matrix.size();
    const int nColumns = matrix[0].size();
    int i = 0;
    int j = matrix[0].size() - 1;
    while ( i >= 0 && i < nRows
            && j >= 0 && j < nColumns) {
        if (target == matrix[i][j]) {
            return true;
        } else if (target < matrix[i][j]) {
            j--;
        } else {
            i++;
        }
    }
    return false;

}

int main() {
    vector<vector<int>> matrix = {{1,   4,  7, 11, 15},
  {2,   5,  8, 12, 19},
  {3,   6,  9, 16, 22},
  {10, 13, 14, 17, 24},
  {18, 21, 23, 26, 30}
};
cout << searchMatrix(matrix, 5) << endl;

}