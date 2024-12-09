#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    // Find the element closet to X (use std::lower_bound -> returns first >= elemeent
    // mark that as R. Mark the element to the left (R-1 ) as L
    // 
    // Now we want to build a window such that we have k elements
    // If arr[L] - x <= arr[R]  - x, the distance on right is too large, expand left
    // If arr[R] - x <= arr[L] - x , distance on the left is too large, expand right
    
    // as we expand, we guarantee that [L+1][R] is valid, so jsut return that
	auto found =  std::lower_bound(arr.begin(), arr.end(), x);
	int R = found - arr.begin();
	int L = R - 1;
	auto N  = arr.size();
	for (int i = 0; i < k; i++){
		if (R >= 0 && R < N &&  L >= 0 && abs(arr[R] -x) <= abs(arr[L]-x)) {
			L--;
		} else {
			R++;
		}
	}
	return vector<int>(arr.begin() + L + 1, arr.begin() + R);
    
}

int main() {
	
	vector<int> arr = {1,2,3,4,5};
	auto res = findClosestElements(arr, 4,3);
	for (auto n : res) {
		cout << n << " , ";
	}

	cout << endl;
	arr = {1,1,2,3,4,5};
	 res = findClosestElements(arr, 4,-1);
	for (auto n : res) {
		cout << n << " , ";
	}
}