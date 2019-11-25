#include <iostream>
#include <vector>
using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        auto& xArr = nums1;
        auto& yArr = nums2;
        if (xArr.size() > yArr.size())
            std::swap(xArr, yArr);
        // Want to find partition X + partitiony s.t pX + pY = (len(X) + len(Y) + 1 ) /2
        // If total length is odd, max(pX, pY) will be median
        // If total length is even, average(max(px-1, py-1), min(px,pY))
        // Parittion points are offsets where everything left of the max of both offsets is <= min of both offset
        const int midpoint = (xArr.size() + yArr.size()) / 2;
        int start = 0;
        int end = xArr.size();
        while (true)
        {
            int px = (start + end) / 2;
            int py = midpoint - px;
            auto pxmin = px -1 < 0 ? INT_MIN : xArr[px-1] ;
            auto pymin = py -1 < 0 ? INT_MIN : yArr[py-1];
            auto pxmax = px >= xArr.size() ? INT_MAX : xArr[px];
            auto pymax = py >= yArr.size() ? INT_MAX: yArr[py];
            cout << " px" << px << " py" << py << endl;
            if (pxmin <= pymax && pymin <= pxmax)
            {
                // found
                 cout << "found px" << pxmax << " py" << pymax << endl;

                if ( (xArr.size() + yArr.size()) % 2 == 1) // odd
                {
                    return min(pxmax, pymax);
                }
                else // even
                    return (max(pxmin, pymin) + min(pxmax, pymax)) / 2.0f;
            }
            else if (pxmin > pymax)
            {
                // move left
                end = px - 1;
            }
            else
            {
                // move right
                start = px + 1;
            }
        }
    }

int main() {
    vector<int> v1 = {1,3};
    vector<int> v2 = {2};
    assert(findMedianSortedArrays(v1, v2) == 2);
    v1 = {1,2};
    v2 = {3,4};
    assert(findMedianSortedArrays(v1, v2) == 2.5f);
}