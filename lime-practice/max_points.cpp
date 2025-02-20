#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <string>
using namespace std;

int maxPoints(vector<vector<int>>& points) {
    // For a given point , compare with every other point, and compute the slope
    // Maintain a mapping of slopes
    // If point is the same as the current point, append it
    // If point has the same x coordinate it, infiniteSlope add
    // at the end compute the local maximal = max(slopeMax + 1, samePoint + 1)
    // Update global maximal
    // Because we don't compute slope as it produces a decimal value and we can't store that correctly
    // Use a string where we divide both numerator and denominatr by gcd

    int result = 0;
    for (int i = 0; i < points.size(); i++)
    {
        auto p0x = points[i][0];
        auto p0y = points[i][1];
        int localmax = 0;
        int infinity = 0;
        unordered_map<string, int> slopeCount;
        int samePoint = 0;
        for (int j = 0; j < points.size(); j++)
        {
            if (i == j) continue;
            auto p1x = points[j][0];
            auto p1y = points[j][1];
            if (p1x == p0x && p1y == p0y)
                samePoint++;
            else if (p0x == p1x) {
                infinity++;
            } else {
                auto mx = p1x - p0x;
                auto my = p1y - p0y;
                int gcd = std::gcd(std::abs(my), std::abs(mx));
                if (mx == -1 && my ==-1) {
                    mx = -1 * mx;
                    my = -1 * my;
                } else if (my == -1) {
                    mx = -1 * mx;
                    my = abs(my);
                }// else positive
                mx = mx / gcd;
                my = my /gcd;
                string key = to_string(my) + "_" + to_string(mx);
                if (slopeCount.find(key) == slopeCount.end())
                    slopeCount[key] = 1;
                else
                    slopeCount[key]++;
                localmax = max(slopeCount[key], localmax);
            }
        }
        localmax = max(samePoint + localmax + 1 , samePoint + infinity + 1);
        result = max(localmax, result);
    }
    return result;
}

int main() {
    vector<vector<int>> v= {{1,1},{2,2},{3,3}};
    cout << maxPoints(v) << endl;
    vector<vector<int>> v2 = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
        cout << maxPoints(v2) << endl;


}