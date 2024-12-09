#include <iostream>
using namespace std;

double myPow(double x, int n) {
    // If n is even , compute the result of x ^ (n/2) then multiple by this result
    // If n is odd, compute the result of x^(n -1) * (x), then multiply
    // if n is 1 return x
    // if n is 0 , return 1;
    // If n is INT_MIN , need special care
    if (n < 0) {
    	if (n == INT_MIN){
			return 1/ (myPow(x, INT_MAX) * x);
    	} else {
    		return 1/ myPow(x, -1 * n);
   		 }
    }
    else if (n == 0) {
    	return 1;
    } else if (n == 1) {
    	return x;
    } else {
    	if (n % 2 == 1) {
    		return myPow(x, n-1)  * x;
    	} else {
    		auto result = myPow(x, n /2);
    		return result * result;
    	}
    }
}
int main() {
	assert(myPow(2, 10) == 1024);
	cout << myPow(2.1, 3) << endl;
	cout <<myPow(2, -2) <<endl;
	cout << myPow(1.00000, -2147483648) << endl;
}
