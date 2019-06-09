#include <iostream>
#include <vector>
using namespace std;

 bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;
        int startRow = 0;
        int endRow = matrix.size() - 1;
        int targetRow = -1;
        while (startRow <= endRow)
        {
            int mid = (startRow + endRow) / 2;
            if (target > matrix[mid].back())
            {
                startRow = mid + 1;
            }
            else if (target < matrix[mid].front())
            {
                endRow = mid - 1;
            }
            else 
            {
                targetRow = mid;
                break;
            }
        }
        // Find the target row then find the target column
        if (targetRow == -1)
            return false;

        int startCol = 0;
        int endCol = matrix[targetRow].size() - 1;
        cout << "here" << targetRow << endl;
        while (startCol < endCol)
        {
            int mid = (startCol + endCol) /2;
            cout << mid << endl;
             if (target < matrix[targetRow][mid])
            {
            	            	cout << "Herebad1" << endl;

                endCol = mid -1;
            }
            else if (target > matrix[targetRow][mid])
            {
            	            	cout << "Herebad" << endl;

                startCol = mid + 1;
            }
            else {
            	cout << "Here2" << endl;
                return true;
            }
        }
        return false;
    }

int main() {
	vector<vector<int>>  mat = {{1}};
	cout << searchMatrix(mat, 1) << endl;

}