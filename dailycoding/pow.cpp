#include <iostream>
using namespace std;

double helper(double x, long n)
    {
        if (n == 1)
            return x;
        else
        {
            double helperRes = helper(x, n /2);
            double val = helperRes* helperRes * (( n % 2 == 1) ? x  : 1);
            return val;
        }
    }

    double myPow(double x, int n) {
        if (n == 0 )
            return static_cast<double>(1);
       auto result = helper(x, static_cast<long>(std::abs(n)));
        if (n < 0 )
            result = 1 / result;

        return result;
    }

int main()
{
    cout << myPow(2.00000,-2) << endl;
}