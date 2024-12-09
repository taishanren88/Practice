#include <iostream>
#include <vector>
using namespace std;
class ProductOfNumbers {
public:
	// 2,3,4 => k = 2, product= [1,2,6,24], result = 12
    ProductOfNumbers() {
        // Maintain a list of running products where you have a sentinel of 1
        // If the current num is 0, clear the list and have a sentinel of 1
        // At the end, product of last k is (result[last] / result[last- k]
        products = {1};
    }
    
    void add(int num) {
    	if (num == 0 ) {
    		products = {1};
    		return;
    	}
        
        products.push_back(products.back()  * num);
    }
    
    int getProduct(int k) {
    	if (products.size() <= k ) {
    		return 0;
    	}
    	return products.back() / products[products.size() - 1 - k];
        
    }
    vector<int> products;

};


int main() {
	ProductOfNumbers productOfNumbers;
	productOfNumbers.add(3);        // [3]
	productOfNumbers.add(0);        // [3,0]
	cout << productOfNumbers.getProduct(1) << endl;
	productOfNumbers.add(2);        // [3,0,2]
	productOfNumbers.add(5);        // [3,0,2,5]
	productOfNumbers.add(4);        // [3,0,2,5,4]
	cout << productOfNumbers.getProduct(2) <<endl; // return 20. The product of the last 2 numbers is 5 * 4 = 20
	 cout << productOfNumbers.getProduct(3) << endl; // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40

// 3,0,2,5,4,
	 // {1,3}
     // {1}
	 cout << productOfNumbers.getProduct(4) << endl; // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
	 // productOfNumbers.add(8);        // [3,0,2,5,4,8]
	 // cout << productOfNumbers.getProduct(2) << endl; // return 32. The product of the last 2 numbers is 4 * 8 = 32 }
}
