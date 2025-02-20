#include <iostream>
#include <math.h>
using namespace std;

int countOrders(int n) {
	// every order has 2 events P, and D
	// We know for sure there will be n! permutations of pickups there are n! events
	// If n = 1 , P1 , D1 (1 permutation)
	// If n = 2 , let's say  one order looks like this P1_P2_,
	//  then we have P1_P2D2 ( 1)
	//  then , we have P1_P2_D2_ (3)
	// so if n =2 , we have 1 * 3
	// If n =3 , lets' say one permutations looks like this P1_P2_P3,
	// then we have 
	// P1P2_P3D3 (1)
	// P1 P2_P3_D3_ (3)
	// P1 P2 D2 P3 D3 (5)
	// so if n = 3, we have 1 * 3 * , ... 2 *n - 1 permutations for a single set of pickups

	// so we have n! * (1 * 3 * 2n-1);

	long result = 1;
	long cap = pow(10,9) + 7;
	for (int i = 1; i <= n; i++) {
		result = (result * i)% cap;
	}
	for (int i = 1 ; i <= (2*n -1); i+=2) {
		result = (result * i) % cap;
	}
	return result;
}

int main() {
	assert(countOrders(1) == 1);
	assert(countOrders(2) == 6);
	assert(countOrders(3) == 90);
	assert(countOrders(18) == 368349166);


}