#include <iostream>
#include <vector>
#include <string>

using namespace std;

void dfs(const string& digits, int pos, string curr, vector<string>& results)
{
	if (pos == digits.size())
	{
		results.push_back(curr);
		return;
	}
    static vector<vector<char>> mapping = {{'a','b','c'},
									{'d', 'e', 'f'}, 
									{'g', 'h', 'i'},
									{'j', 'k','l'},
									{'m', 'n' , 'o'},
									{'p', 'q', 'r', 's'},
									{'t' ,'u', 'v'},
									{'w', 'x', 'y', 'z'}};
	int currDigit = digits[pos] - '0';
	for (char c : mapping[currDigit - 2])
	{
		dfs(digits, pos +1, curr + c, results);
	} 

}

vector<string> letterCombinations(string digits) {
	vector<string> results;
	dfs(digits, 0, "", results);
	return results;
}

int main()
{
	auto res = letterCombinations("23");
	for_each(res.begin(), res.end(), [](string &str ) {
		cout << str << ",";
	});
}