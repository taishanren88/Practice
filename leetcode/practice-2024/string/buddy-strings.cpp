#include <iostream>
#include <unordered_map>
using namespace std;

bool buddyStrings(string A, string B) {
	// If A's size is not same as B size  => false
	// Iterate over string A and keep trakc of charater counts
	// If any time A != B, mark the difference. If more than 2 => false
	// Post process: If 2 different , check that A[different_1] == B[different_2]
	// and B[different_1] == A [different_2] => false
	
	// Otherwise if A == B check if tehre's any character with a a character count > 1 
	// Else false

 if (A.size() != B.size()) {
 	return false;
 }

 unordered_map<char, int> charCounts;
 int firstDifferentPos = -1;
 int secondDifferentPos = -1;
 for (int i = 0; i < A.size(); i++) {

 	if (A[i] != B[i]) {
 		if (firstDifferentPos == -1) {
 			firstDifferentPos = i;
 		} else if (secondDifferentPos == -1) {
 			secondDifferentPos = i;
 		} else {
 			return false;
 		}
 	}
 	charCounts[A[i]]++;
 }

 if (firstDifferentPos != -1 && secondDifferentPos != -1) {
 	return A[firstDifferentPos] == B[secondDifferentPos] 
 	&&  A[secondDifferentPos] == B[firstDifferentPos];
 }
 if (A == B) {
 	for (auto kv : charCounts) {
 		if (kv.second > 1) {
 			return true;
 		}
 	}
 }
 return false;

}

int main() {
	
}