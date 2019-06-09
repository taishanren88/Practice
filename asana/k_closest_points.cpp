#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int partition(vector<vector<int>>& points, int start, int end);
vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    // k closest points using quickselect,
	// parittion based on any pivot.
	// Everything < pivot on left, > pivot on right
	// Return pivotIndex
	// If we determine pivotIndex == k, we are done. Average time : O(n), but could be O(n^2)
	int start = 0;
	int end = points.size() - 1;
	while (start <= end)
	{
		auto pivotIndex = partition(points, start, end);
		if (pivotIndex == K)
			return vector<vector<int>>(points.begin(), points.begin() + K);
		if (pivotIndex > K)
			end = pivotIndex - 1;
		else if (pivotIndex < K)
			start = pivotIndex + 1;
	}
	return points;
}

int compare(vector<int>& a, vector<int>& b){
	auto firstVal = (a[0] * a[0] + a[1] * a[1]) ;
	auto secondVal = (b[0] * b[0] + b[1] * b[1]);
	return firstVal - secondVal ;
}
int partition(vector<vector<int>>& points, int start, int end)
{
	auto pivotIndex = start;
	auto pivot = points[pivotIndex];
    int lessThanPivot = start;
    int greaterThanPivot = end;
    int unknown = lessThanPivot;
    while (unknown <= greaterThanPivot) {
        if (compare(points[unknown], pivot) < 0)
        {
            swap(points[unknown], points[lessThanPivot]);
            lessThanPivot++;
            unknown++;
        }
        else if (compare(points[unknown], pivot) > 0)
        {
            swap(points[unknown], points[greaterThanPivot]);
            greaterThanPivot--;
        }
        else
        {
            unknown++;
        }
    }

    return greaterThanPivot;
}
int total(vector<vector<int>>vec)
{
	int total = 0;
	for (auto a : vec)
		total += a[0] * a[0] + a[1]*a[1];
	return total;
}
int main() {

	 vector<vector<int>> vec = {{1,3},{-2,2}, {2,-2}};
	assert(total(kClosest( vec, 1)) == total({{-2,2}}));
	// cout << endl;
	 vec = {{-2,10},{-4,-8},{10,7},{-4,-7}};
	// auto res = kClosest( vec, 3);
	// for (auto a : res)
	// 	cout << a[0] << "," << a[1] << "...";
	cout << endl;
	kClosest( vec, 3);
	assert(total(kClosest( vec, 3)) == total({{4,-7},{-4,-8},{-2,10}}));
}