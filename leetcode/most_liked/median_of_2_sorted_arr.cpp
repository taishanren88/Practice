#include <iostream>
#include <vector>
using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        auto& xArr = nums1;
        auto& yArr = nums2;
       // if (xArr.size() > yArr.size())
      //      std::swap(xArr, yArr);
        // Want to find partition X + partitiony s.t pX + pY = (len(X) + len(Y) ) /2
        // px, py represent the right side of the partition point
        // If total length is odd, max(pX, pY) will be median
        // If total length is even, average(max(px-1, py-1), min(px,pY))
        // Parittion points are offsets where everything left of the max of both offsets is <= min of both offset
        // If pxLeft <= pyRight && pyLeft <= pxRight, we are done
        // If pxLeft > pyRight, px is  too big, move left
        // If pyLeft > pxRight, pY is too large, move pX  right
        const int midpoint = (xArr.size() + yArr.size()) / 2;
        int start = 0;
        int end = xArr.size();
        while (true)
        {
          const auto pxRightIndex = (start + end) / 2;
          const auto pxLeftIndex = pxRightIndex - 1;
          const auto pyRightIndex = midpoint - pxRightIndex;
          const auto pyLeftIndex = pyRightIndex -1;
          const auto pxLeft = pxLeftIndex < 0 ? INT_MIN : xArr[pxLeftIndex];
          const auto pxRight = pxRightIndex >= xArr.size() ? INT_MAX : xArr[pxRightIndex];
          const auto pyLeft = pyLeftIndex < 0 ? INT_MIN : yArr[pyLeftIndex];
          const auto pyRight = pyRightIndex >= yArr.size() ? INT_MAX: yArr[pyRightIndex];
          cout << " px" << pxRightIndex << " py" << pyRightIndex << endl;

          if (pxLeft <= pyRight && pyLeft <= pxRight) {
          		if ( (xArr.size() + yArr.size()) % 2 == 1) {
          			return std::min(pyRight, pxRight);
          		} else {
          			return (std::max(pyLeft, pxLeft) + std::min(pxRight, pyRight)) / 2.0f;
          		}
          } else if (pxLeft > pyRight) {
          	end = pxRightIndex - 1;
          	cout << "moving left "<< endl;
          } else {
          	start = pxRightIndex + 1;

          }
      	}
    }


int main() {
	vector<int> x = {1,2};
	vector<int> y = {3,4};
	cout << findMedianSortedArrays(x,y) << endl;

	x = {1,3};
	 y = {2};
	cout << findMedianSortedArrays(x,y) << endl;

	x = {1,3};
	 y = {4};
	cout << findMedianSortedArrays(x,y) << endl;

	x = {10};
	 y = {11};
	cout << findMedianSortedArrays(x,y) << endl;

}