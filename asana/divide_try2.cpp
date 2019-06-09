#include <iostream>
#include <cassert>

using namespace std;

long long_divide(long dividend, long divisor) {
	if (dividend < divisor)
		return 0;
	auto multipleCount = 1;
	auto sum = divisor;
	while (( sum + sum )<= dividend)
	{
		sum += sum;
		multipleCount += multipleCount;
	}
	return multipleCount + long_divide(dividend - sum, divisor);
}

int divide(int dividend, int divisor) {

	if (dividend == INT_MIN && divisor == -1)
	{
		return INT_MAX;
	}
	bool isNeg = (dividend <0 && divisor > 0)|| (dividend >0 && divisor < 0);
	auto result = long_divide(std::abs(static_cast<long>(dividend)), std::abs(static_cast<long>(divisor)));
	if (isNeg)
		result *= -1;
	return result;
}

int main () {
	assert(divide(INT_MIN, -1) == INT_MAX);
	assert(divide(INT_MAX, 1) == INT_MAX);
    assert(divide(6,3) == 2);
    assert(divide(6,4) == 1);
}