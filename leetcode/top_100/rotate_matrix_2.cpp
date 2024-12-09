#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<vector<int>>& matrix) {
	// Iterate row by row . swap matrix[r][c] with matrix[n-1-c][[n-1-r]
	// only swap c < n- r -1 number of times
	int count = matrix.size() - 1;
	const auto N = matrix.size();
	for (int r = 0; r < matrix.size(); r++) {
		for (int c  = 0 ; c < count; c++) {
			swap(matrix[r][c], matrix[N - 1 - c][N - 1 - r]);
		}
		count--;
	}
	// swap the rows at the end
	for (int i = 0; i < matrix.size() / 2 ; i++) {
		swap (matrix[i], matrix[N - 1 - i]);
	}
}

int main() {
	vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	rotate(mat);
	auto print = [](vector<vector<int>> mat) {
		cout << endl;
		for (int i = 0 ; i < mat.size() ; i++) {
			for (int j = 0; j < mat[i].size(); j++) {
				cout << mat[i][j] << ",";
			}
			cout << endl;
		}
	};
	print(mat);
	mat = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
	rotate(mat);
	print(mat);

	mat = {{1}};
	rotate(mat);
	print(mat);

}