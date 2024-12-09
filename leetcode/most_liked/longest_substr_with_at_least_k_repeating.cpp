/*
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/

// For varying amount ('x) of unique characters (1->26), find maxmum substring where characters appear at least k times

// Two pointer, window moving
// For a given 'x'
// If # of unique characters <= 'x', move right pointer, update counts
// If  == 'x', check if we have at least k for all characters (Once found, don't need to keep checking). IF so update the maximum substring
// If # of unique characters > 'x', move left pointer, update counts


#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


int getMaxLenForUniqueCharacters(std::string s, int numUnique, int k) {
// Loop through the string, maintain right window and left window pointers
// If number of characters is <= "numUnique", update unique character count, and also advance right pointer
// If number of characters is > "numUnique", update unique character counts, and also advance left pointer
	int maxLen = 0;
	int right = 0;
	int left = 0;
	unordered_map<char, int> characterCounts;

	auto checkCounts =[&]() {
		for (auto& kv: characterCounts) {
			if (kv.second < k) {
				return false;
			}
		}
		return true;
	};
	for (; right < s.size(); right++) {
		characterCounts[s[right]]++;
		while (characterCounts.size() > numUnique) {
			characterCounts[s[left]]--;
			if (characterCounts[s[left]] == 0) {
				characterCounts.erase(s[left]);
			}
			left++;
		}
		if (characterCounts.size() == numUnique
			&& checkCounts()) {
			maxLen = max(maxLen, right - left + 1);
		}
	}
	return maxLen;
}

int longestSubstring(string s, int k) {
	int maxLength = 0;
	for (int i = 1 ; i <= 26; i++) {
		maxLength = max(getMaxLenForUniqueCharacters(s, i, k), maxLength);
	}
	return maxLength;
}
int main() {

// 1 unque character with lenght at least 1 each
	assert(getMaxLenForUniqueCharacters("a", 1, 1) == 1);
// 1 unque chracter ,with length at least 1 each
	assert(getMaxLenForUniqueCharacters("aab", 1, 1)  == 2);
// 1 unque chracter ,with length at least 2 each
	assert(getMaxLenForUniqueCharacters("aab", 1, 2)  == 2);
	// 1 unque chracter ,with length at least 3 each
	assert(getMaxLenForUniqueCharacters("aab", 1, 3)  == 0);

	// 1 unque chracter ,with length at least 3 each
	assert(getMaxLenForUniqueCharacters("aabbb", 1, 3) == 3);
	// 
	assert(getMaxLenForUniqueCharacters("aabbb", 2, 2) == 5);
	// two unique charactesr with length of 3 each
	assert(getMaxLenForUniqueCharacters("aabbb", 2, 3) == 0);

	// reverse the input
	assert(getMaxLenForUniqueCharacters("bbbaa", 1, 3) == 3);
	// 
	assert(getMaxLenForUniqueCharacters("bbbaa", 2, 2) == 5);
	// two unique charactesr with length of 3 each
	assert(getMaxLenForUniqueCharacters("bbbaa", 2, 3) == 0);

	// two unique characters with length of 2 each
	assert(getMaxLenForUniqueCharacters("ababbc", 2, 2) == 5);


	assert(longestSubstring("aaabb", 3) == 3);
	assert(longestSubstring("ababbc", 2) == 5);

}
