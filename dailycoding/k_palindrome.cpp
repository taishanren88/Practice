#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

/*
Given a string which we can delete at most k, return whether you can make a palindrome.

For example, given 'waterrfetawx' and a k of 2, you could delete f and x to get 'waterretaw'.
*/

/* Approach 1:
Find longest common palindromic subsequence.
L : Lenght of original string
S : Longest paindromic subsequence

Want to be <= k edits, which means that L - S  <= k
*/
int longestPalindromicSubsequence(string s)
{
	if (s.empty()) 
		return 0;
	vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
	for (int i = 0; i < s.size(); i++)
	{
		dp[i][i] = 1;
	}

	int longest = 1;
	// Length 2 palindromes and above
	for (int k = 1; k < s.size(); k++)
	{
		int j = k;
		int i = 0;
		for (int j = k ; j < s.size(); i++, j++)
		{
			if (s[i] == s[j])
			{
				 dp[i][j] = dp[i+1][j-1] + 2;
				 longest = max(longest, dp[i][j]);
			}
			else
			{
				dp[i][j] = max(dp[i][j-1], dp[i+1][j]);
			}
		}
	}
	return longest;
}

/* Approach 2:
Find minimum edit distance to make palindrome of current string,
where we can only delete

Since edit distance is edits for both strings , we
Want 2 * edit distance <= 2 * k
*/

// Here we just use approach 1
bool kPalindrome(string s, int k)
{
	return s.size() - longestPalindromicSubsequence(s) <= k;
}

int main()
{
	assert(longestPalindromicSubsequence("a") ==1);
	assert(longestPalindromicSubsequence("aa") == 2);
    assert(longestPalindromicSubsequence("aba") == 3);
    assert(longestPalindromicSubsequence("cbbd") == 2);
    assert(longestPalindromicSubsequence("bbbab") == 4);
    assert(longestPalindromicSubsequence("GEEKSFORGEEKS") == 5);

	// assert(longestPalindromicSubsequence("abac") == 3);
	// cout << "Longest palindrome of " << longestPalindromicSubsequence("waterrfetawx") << endl;
	 assert(kPalindrome("waterrfetawx", 2)); 
	 assert(!kPalindrome("waterrfetawx", 1)); 
}