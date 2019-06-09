#include <iostream>
#include <vector>
using namespace std;

/*
A very hungry rabbit is placed in the center of of a garden,
represented by a rectangular N x M 2D matrix.
The values of the matrix will represent numbers of carrots
available to the rabbit in each square of the garden. If the garden
does not have an exact center, the rabbit should start in the
square closest to the center with the highest carrot count.
On a given turn, the rabbit will eat the carrots available on the
square that it is on, and then move up, down, left, or right,
choosing the the square that has the most carrots. If there are no
carrots left on any of the adjacent squares, the rabbit will go to
sleep. You may assume that the rabbit will never have to choose
between two squares with the same number of carrots.
Write a function which takes a garden matrix and returns the number
of carrots the rabbit eats. You may assume the matrix is rectangular with at least 1 row and 1 column, and that it is populated with non-negative integers. For example: 
[[5, 7, 8, 6, 3],
[0, 0, 7, 0, 4],
[4, 6, 3, 4, 9],
[3, 1, 0, 5, 8]]
Should return: 
27
*/
int numRabbitCarrots(vector<vector<int>> matrix)
{
	if (matrix.empty())
		return 0;
	int numRows = matrix.size();
	int numCols = matrix[0].size();
	auto getMaxLoc=[&matrix, numRows, numCols](int row, int col, int &oMaxRow, int& oMaxCol, int& oMaxVal) {
			if (row >=0 && col >=0 && row < numRows && col < numCols
				&& matrix[row][col] > oMaxVal)
			{
				oMaxVal = matrix[row][col];
				oMaxRow = row;
				oMaxCol = col;
			}
		};

	auto getCenter=[&]() {
		int i = numRows /2;
		int j = numCols / 2;
		int maxVal = matrix[i][j];

		int maxRow = i;
		int maxCol = j;
		getMaxLoc( (numRows - 1 )/ 2, j, maxRow, maxCol, maxVal);
		getMaxLoc(i, (numCols - 1) / 2, maxRow, maxCol, maxVal);
		getMaxLoc((numRows -1) / 2,  (numCols - 1) / 2, maxRow, maxCol, maxVal);
		return make_pair(maxRow, maxCol);
	};
	auto center = getCenter();
	auto i = center.first;
	auto j = center.second;
	int numCarrots = matrix[i][j];

	int nextI, nextJ;
	int result = 0;
	while (numCarrots != 0)
	{
		result += numCarrots;
		matrix[i][j] = 0;
		// advance
		numCarrots = 0;
		getMaxLoc(i-1, j, nextI, nextJ, numCarrots);
		getMaxLoc(i+1, j, nextI, nextJ, numCarrots);
		getMaxLoc(i, j -1, nextI, nextJ, numCarrots);
		getMaxLoc(i, j + 1, nextI, nextJ, numCarrots);

		i = nextI;
		j = nextJ;
	}

	return result;
}
int main() {
	cout << "number of carrots" << numRabbitCarrots({{5, 7, 8, 6, 3},
{0, 0, 7, 0, 4},
{4, 6, 3, 4, 9},
{3, 1, 0, 5, 8}}) << endl;

}