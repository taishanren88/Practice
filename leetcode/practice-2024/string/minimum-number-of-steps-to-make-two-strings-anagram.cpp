#include <iostream>
#include <unordered_map>
using namespace std;

int minSteps(string s, string t) {
	// Check if string size is same. If not => false
	//  Iterate over one string, accumulate  char counts 
	//  Iterate over other strip, decrement char counts
	//  If any char count at the end is > count those. That's the minimum of teps
	//  We don't care about negative char counts because for each thing that is less we have , because they cancel out
	//  e.g. bab  => {b:2, a: 1}  against aba : [b:1 , a:-1]. 
	//  If I change  aba => to bba  , it will be b:2 , a: 1 
	
	
	unordered_map<char, int> charCounts;
	for (int i = 0 ; i < s.size(); i ++) {
		charCounts[s[i]]++;
	}
	int result = 0;
	for (int i = 0; i < t.size(); i++){
		if(charCounts.find(t[i]) == charCounts.end() ||charCounts[t[i]] == 0){
			result++;
		} else {
			charCounts[t[i]]--;
		}
	}

	return result;
}

int main() {

}