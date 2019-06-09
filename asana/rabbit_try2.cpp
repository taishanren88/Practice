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
	if (matrix.empty() || matrix[0].empty())
		return 0;

	// Given an input row/column, adjusts the maximum value and location if max
	auto getMax =[&matrix](int row, int col, int& oRow, int& oCol, int& maxVal) {
		if (row >= 0 && row < matrix.size()
			&& col >= 0 && col < matrix[0].size())
		{
			if (matrix[row][col] > maxVal)
			{
				oRow = row;
				oCol = col;
				maxVal = matrix[row][col];
			}
		}
	};
	const int nRows = matrix.size();
	const int nCols = matrix[0].size();
	int valueAtCenter =0;
	int centerX;
	int centerY;
	getMax(nRows /2, nCols / 2, centerX, centerY, valueAtCenter);
	getMax((nRows -1) /2, nCols / 2, centerX, centerY, valueAtCenter);
	getMax((nRows -1) /2, (nCols -1)/ 2, centerX, centerY, valueAtCenter);
	getMax(nRows /2, (nCols -1)/ 2, centerX, centerY, valueAtCenter);

	int result = 0;
	int row = centerX;
	int col = centerY;
	bool moreCarrots = true;
	while (moreCarrots)
	{
		result += matrix[row][col];
		int maxRow, maxCol;
		int numCarrots = 0;
		// look in other directions
		getMax(row - 1, col, maxRow, maxCol, numCarrots);
		getMax(row +  1, col, maxRow, maxCol, numCarrots);
		getMax(row, col - 1, maxRow, maxCol, numCarrots);
		getMax(row, col + 1, maxRow, maxCol, numCarrots);
		matrix[row][col] = 0;

		row = maxRow;
		col = maxCol;
		moreCarrots = numCarrots > 0;
	}
	return result;
}
int main() {
	assert(numRabbitCarrots({{5, 7, 8, 6, 3},
{0, 0, 7, 0, 4},
{4, 6, 3, 4, 9},
{3, 1, 0, 5, 8}}) == 27);
	assert(numRabbitCarrots({
			{2, 7, 8, 3},
			{0, 0, 7, 4},
			{4, 6, 3, 9},
			{3, 1, 0, 8}}) == 24);
	assert(numRabbitCarrots({
			{2, 0, 8, 3},
			{0, 7, 5, 4},
			{4, 6, 3, 9},
			{3, 1, 0, 8}}) == 21);

}