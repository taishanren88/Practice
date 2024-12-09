#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
	vector<vector<int>> results(mat1.size(), vector<int>(mat2[0].size(), 0));
	auto m = mat1.size();
	auto n = mat2[0].size();
	for (int i = 0 ; i < m ; i++ ) {
		for (int k = 0 ; k < n; k++) {
			auto res = 0;
			for (int j = 0; j < mat1[i].size(); j++) {
				printf("(%d,%d) x (%d,%d) ... ", i,j, j,k);
				res = res + mat1[i][j] * mat2[j][k];
			}
			cout << endl;
			// cout << res << ",";
			results[i][k] = res;
			// cout << endl;
		}
	}
	return results;
}


int main() {
	vector<vector<int>> mat1 = {{1, 0, 0}, { -1, 0, 3}};
	vector<vector<int>> mat2 = {{7, 0, 0}, {0, 0, 0}, {0, 0, 1}};
	auto res =	multiply (mat1, mat2);
	for (int i = 0; i < res.size(); i ++) {
		for (int j = 0 ; j < res[i].size(); j++) {
			cout << res[i][j] << ", " ;
		}
		cout << endl;
	}
	// 
	 mat1 = {{1,-5}};
	 mat2 = {{12}, {-1}};
	res =	multiply (mat1, mat2);
	for (int i = 0; i < res.size(); i ++) {
		for (int j = 0 ; j < res[i].size(); j++) {
			cout << res[i][j] << ", " ;
		}
		cout << endl;
	}
}