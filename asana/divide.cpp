#include <iostream>
#include <cassert>
using namespace std;

 long long_divide(long dividend, long divisor) {
        if (dividend < divisor)
            return 0;
        
        auto sum = divisor;
        int multiple = 1;
        while (sum + sum < dividend) {
            sum += sum; // double it each time
            multiple += multiple;
        }
        return multiple + long_divide(dividend - sum, divisor);
    }
    int divide(int dividend, int divisor) {
        // Count how many times you can subtract divisor from dividend
        // Since we want to do this faster than linear subtracting
        // Count the # of times you can subtract but double those times each time
        // Convert to long to handle integer overflow case
        bool isNeg = (dividend < 0 && divisor > 0) || (dividend >0 && divisor < 0);
        if (dividend == INT_MIN && divisor == 1)
            return INT_MIN;
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

       auto result = long_divide(abs(static_cast<long>(dividend)), abs(static_cast<long>(divisor)));
        if (isNeg)
            result *= -1;
        return result;
    }

    int main() {

    	assert(divide(INT_MIN, -1) == INT_MAX);
    	assert(divide(INT_MAX, 1) == INT_MAX);
        assert(divide(6,3) == 2);
        assert(divide(6,4) == 1);


    }