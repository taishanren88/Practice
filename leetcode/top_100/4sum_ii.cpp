#include <iostream>
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

/**
Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in the range of -228 to 228 - 1 and the result is guaranteed to be at most 231 - 1.

Example:

Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
*/

int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    // Want to find number of tuples A[i] + B[j] + C[k] + D[l] == 0
    // Or find number of tuples A[i] + B[j] = - (C[k] + D[l])
    // Count all 2 sums of C[k] + D[l]. Maintain a mapping of sum -> count
	// Loop through A[i], B[j]. If A[i] + B[j] == - (C[k] + D[l])), add their counts in
	unordered_map<int, int> mapping;
	for (int k = 0; k < C.size() ; k++) {
		for (int l = 0 ; l  < D.size() ; l++ ){
			int sum = C[k] + D[l];
			if (mapping.find(sum) == mapping.end()) {
				mapping[sum] = 1;
			} else {
				mapping[sum]++;
			}
		}
	}
	int result = 0;
	for (int i = 0; i < A.size() ; i++) {
		for (int j = 0; j < B.size() ; j++) {
			int sum = A[i] + B[j];
			if (mapping.find(-sum) != mapping.end()) {
				result += mapping[-sum];
			}
		}
	}
	return result;
}
int main() {
	vector<int> A = {1,2};
	vector<int> B = {-2, -1};
	vector<int> C = { -1, 2};
	vector<int> D = {0, 2};
	assert(fourSumCount(A,B,C,D) == 2);

	A = {0, 1, -1};
	B = { -1, 1, 0};
	C = {0, 0 ,1};
	D = {-1, 1, 1};
	assert(fourSumCount(A,B,C,D) ==17);
}