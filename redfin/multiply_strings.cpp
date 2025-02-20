#include <iostream>
#include <string>
#include <vector>

using namespace std;

string multiply(string num1, string num2) {
	// Loop through evry digit , going from right to left of num2
	// Multiply this with every digit of num1, going from right to left of of num1
	// At each level, you'll have  total sum where sum = (carry + digitProduct) % 10 * place
	// 	carry = (carry + digitProduct) / 10
	// place *= 10
	// maintain a single row vector of 110 digits
	// at each point, take the sum and add it to the digit in that place
	vector<int> sums(110 * 110 , 0);
	auto addFromPlace=[&](int value, int place) {
		int i = sums.size() - place;
	 	int currSum = sums[i] + value;

		sums[i] = currSum % 10;
		int carry = currSum / 10 ;
		return carry;
	};


	int place = 1;
	for (int i = num2.size() - 1; i >= 0; i--, place ++) {
		int placeCurr = place;
		int b = num2[i] - '0';
		int carry = 0;
		for (int j = num1.size() - 1; j >= 0; j-- , placeCurr ++){
			int a = num1[j] - '0';
			int singleProduct = b * a + carry;
			carry = addFromPlace(singleProduct, placeCurr);
		}
		addFromPlace(carry, placeCurr);

	}
	string result = "";
	int i = 0;
	while (i < sums.size() && sums[i] == 0) {
		i++;
	}

	for (; i< sums.size(); i++ ) {
		result += to_string(sums[i]);
	}
	if (result.empty())
		result = "0";

	return result;
}
int main() {
	assert(multiply ("9", "9") == "81");
	 assert(multiply ("9", "0") == "0");

	assert(multiply ("11", "11") == "121");
	assert(multiply ("88", "88") == "7744");
	assert(multiply ("123", "456") == "56088");

}