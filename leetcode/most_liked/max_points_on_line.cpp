   #include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
using namespace std;
int __gcd(int a, int b) 
{ 
    // Everything divides 0  
    if (a == 0) 
       return b; 
    if (b == 0) 
       return a; 
   
    // base case 
    if (a == b) 
        return a; 
   
    // a is greater 
    if (a > b) 
        return __gcd(a-b, b); 
    return __gcd(a, b-a); 
} 
    int maxPoints(vector<vector<int>>& points) {
        // Consider a point with all of the other points
        // If a point is the same x and y values, then it's the same point
        // if a point is the same x value, it's slope is inifnity, 
        // Otherwise, normal slope calculation, typically, we could just calculate the slope. However, slope has precision problems, therefore, let's compute y2 - y1, and x2- x1, and then get the GCD out all of them
        // calculate the maximum at each iteration
        int result = 0;
        for (int i = 0; i < points.size(); i++)
        {
            auto p0x = points[i][0];
            auto p0y = points[i][1];
            int samePoint = 0;
            unordered_map<string, int> slopes; // slope(as string) -> count
            int infinity = 0;
            int localmax = 0;
            for (int j = 0; j < points.size(); j++)
            {
                if (i != j) {
                    auto p1x = points[j][0];
                    auto p1y = points[j][1];
                    if (p1x == p0x && p1y == p0y) {
                        samePoint++;
                    } else if (p1x == p0x) {
                        infinity++;
                    } else {
                        auto xdiff = p1x - p0x;
                        auto ydiff = p1y - p0y;
                        auto mygcd = __gcd(std::abs(xdiff), std::abs(ydiff));
                        xdiff  = xdiff / mygcd;
                        ydiff = ydiff / mygcd;
                        if (xdiff < 0  && ydiff < 0) {
                            xdiff /= -1;
                            ydiff /= -1;
                        } else if (xdiff < 0 || ydiff < 0) {
                            ydiff = -1 * abs(ydiff);
                            xdiff =  abs(xdiff);
                        }
                        string slopeAsStr = to_string(ydiff) + ':' + to_string(xdiff);
                        if (slopes.find(slopeAsStr) == slopes.end()) {
                            slopes[slopeAsStr] = 1;
                        }
                        else {
                            slopes[slopeAsStr]++;
                        }
                        localmax = max(slopes[slopeAsStr], localmax);
                    }
                }
            }       
            result = max(result, max(infinity + samePoint + 1, localmax + samePoint + 1));
        }
        return result;
    }

    int main () {
        vector<vector<int>> points = {{0,0}, {1,1},{1,-1}};
        assert(maxPoints(points) == 2);
        points = {{0,0}, {1,1},{0,0}};
        assert(maxPoints(points) == 3);

        points = {{0,9},{138,429},{115,359},{115,359},{-30,-102},{230,709},{-150,-686},{-135,-613},{-60,-248},{-161,-481},{207,639},{23,79},{-230,-691},{-115,-341},{92,289},{60,336},{-105,-467},{135,701},{-90,-394},{-184,-551},{150,774}};
        assert(maxPoints(points) == 12);


    }