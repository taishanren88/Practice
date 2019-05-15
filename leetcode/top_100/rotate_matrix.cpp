#include <iostream>
#include <vector>
using namespace std;

void rotate(vector<vector<int>>& matrix)
{
	// For each row 
	// For each index in this until current column end, 
	//   swap current element with the n- index element at the n - row column
	// reverse the columns at the end
	const int N = matrix.size();
	int currentColEnd = N - 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < currentColEnd; j++)
		{
			swap(matrix[i][j], matrix[N - 1 - j][N - 1 - i]);
		}
		currentColEnd--;
	}
	//reversre the elements in each column
	for (int j = 0; j < N ; j++)
	{
		for (int i = 0; i < N / 2; i++)
		{
			swap(matrix[i][j], matrix[N - 1 - i][j]);
		}
	}

}

int main()
{
	vector<vector<int>>  matrix= { {1,2,3}, {4,5,6}, {7,8,9}};
	rotate(matrix);
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << "," ;
		}
		cout << endl;
	}
		vector<vector<int>>  matrix2= {   { 5, 1, 9,11},
										  { 2, 4, 8,10},
										  {13, 3, 6, 7},
										  {15,14,12,16}};
	rotate(matrix2);
	for (int i = 0; i < matrix2.size(); i++)
	{
		for (int j = 0; j < matrix2[i].size(); j++)
		{
			cout << matrix2[i][j] << "," ;
		}
		cout << endl;
	}
}