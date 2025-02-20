#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;
void dfs(string num, int pos, int target, string curr, long currVal, long multiply, vector<string>& results) {
	if (pos == num.size()) {
		if (currVal == target)
			results.push_back(curr);
		return;
	};

	for (int i = pos ; i< num.size(); i++ ){
		string currNum = num.substr(pos, i  - pos + 1);
		if (num[pos] == '0' && i > pos) 
			break; // first digit was 0 anyways, we can't append anything after that

		long val = stol(currNum);
		if (curr.empty())  {
			dfs(num, i + 1, target, currNum, val , val, results);
		}
		else {
			dfs(num, i + 1, target, curr + '+' + currNum, currVal + val, val, results);
			dfs(num, i + 1, target, curr + '-' + currNum, currVal - val, -val, results);
			dfs(num, i + 1, target, curr + '*' + currNum, currVal -multiply + multiply * val, multiply * val, results);
		}
	}

}
vector<string> addOperators(string num, int target) {
	// do a dfs where you build substring numbers out of the original sting
    // To do so: , you need to loop from current pos to end 
    // During each iteration, 
    // 1. you create a substring from the start to the current point
	// 2. You apply all 3 operators and go deep
    // 3. Check if the start of the substring was 0, if so we can't do anything and break completely.
	vector<string> results;
	string curr;
	dfs( num , 0, target, curr, 0, 0, results);
	return results;
}

int main() {

	auto res =  addOperators("123", 6);
	for (auto s : res) 
		cout << s << ",";
	assert(res.size() == 2 && (res[0] == "1+2+3" || res[0] == "1*2*3"));
	 res =  addOperators("232", 8);

	 assert(res.size() == 2 && (res[0] == "2*3+2" || res[0] == "2+3*2"));

	 res =  addOperators("00", 0);
	 	for (auto s : res) 
		cout << s << ",";
	assert(res.size() == 3);
	cout << endl;

	auto res2 = addOperators("3456237490", 9191);
	 for (auto s : res2 ) 
		cout << s << ",";
	 assert(res2.empty());
	res2= addOperators("105", 5);
		 for (auto s : res2) 
		cout << s << ",";
	assert(res2.size() == 2);


}