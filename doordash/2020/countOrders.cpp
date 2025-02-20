#include <iostream>
#include <math.h>
using namespace std;

int countOrders(int n) {
	// Intuition: Break up each order into a pair of 2 events
	// It's quite obvious that for every event, we have one pickup
	// So there are n! combination of pickups (P1, P2,...)  or (P2, P1, ...)
	// Now fix a particular combination of pickups 
	// (i.e. : P1_P2_, , there is 1 delivery place for P2 (P1_P2_D2_), then there's 3
	// places for D1. 
	// If  we do the same for 3 orders, there's 1 place for D3, 3 places for D2, 5 place for P1
	// a. P1_P2_P3_ (1)
	// b. P1 P2 _ P3_ D3_(3)
	// c. P1_P2_D2_P3_D3_ (5)

	// meaning for each specific combination, we have 1 * 3 * 5 * ... * (2n-1)
	// Step 1 : Calculate n!
	// Step 2 : calculate 1 * 3 * 5 * ... (2n-1)

	long result = 1;
	int cap = (int)pow (10,9) + 7;
	for (int i = 1; i <= n; i++) {
		result = (result * i) % cap;
	}
	for (int i = 1; i <= (2 * n -1); i+=2) {
		result = (result * i) % cap;
	} 
	return result ;
}

int main() {
	assert(countOrders(1) == 1);
	assert(countOrders(2) == 6);
	assert(countOrders(3) == 90);
	assert(countOrders(18) == 368349166);


}