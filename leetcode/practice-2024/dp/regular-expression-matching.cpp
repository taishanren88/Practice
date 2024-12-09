#include <iostream>
#include <vector>
using namespace std;

bool isMatch(string s, string p) {
	// initialize an array of len(s) x len(p)
	// dp[0][0] = true , empty string against empty pattern is always true
	// dp[i][0] = false, empty pattern matching against "a"
	// dp[0][j] = dp[0][j-2] is empty string matching against some pattern, which can only be true if we have something like "a*"
    
    // everything else 
//     if s[i] == p[j] or p[j] == '.'  => dp[i][j] = dp[i-1][j-1]
    //  if p[j] == '*' => 
    //   	if current character matches char before wildcard , then it's everything up without hte wildcard
    //   	or ignore wildcard (if s[i] == p[j-1] || p[j-1] == '.'  => dp[i][j-2] || dp[i-1][j])
    // otherwise if no match just ignore the wildcard
    //  	dp[i][j] = dp[i][j-2] (none from the wildcard pattern) or
    vector<vector<bool>>table(s.size() + 1, vector<bool>(p.size() + 1, false));
    table[0][0] = true;
    for (int j = 0 ; j< p.size() ; j++) {
    	int jj = j + 1;
    	if (p[j] == '*') {
    		table[0][jj] = table[0][jj-2];
    	}
    }
    for (int i = 0;  i < s.size(); i ++) {
    	int ii =  i + 1;
    	for (int j = 0 ; j < p.size(); j++) {
    		int jj = j + 1;
    		if (p[j] == '*')  {
    			if (s[i] == p[j - 1]  || p[j-1] == '.') {
    				table[ii][jj ] = table[ii-1][jj] || table[ii][jj-2];
    			} else {
					table[ii][jj ] = table[ii][jj-2];
    			}
    		}
    		else if (s[i] == p[j] || p[j] == '.') {
    			table[ii][jj ] = table[ii-1][jj-1];
    		}
    	}
    }
    for (int i = 0; i< table.size() ; i++ ){
    	for (int j =0 ; j < table[i].size() ; j++) {
    		cout << table[i][j] << " ,";
    	}
    	cout << endl;
    }
    return table[s.size()][p.size()];
}

int main() {
	isMatch("ab", ".*");
}