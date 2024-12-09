#include <iostream>
#include <stack>
using namespace std;

5- (2 - (3 - 1) ) 
 int calculate(string s) {
        // We only care about '(', ')', '-'
 	// Keep track of running sign value
 	// If we encounter (, push sign value into a stack
 	// If we enconter - , multiply running sign vs stack top
 	// If we encounter a number apply running sign with the number
 	// If we encounter ), pop top of stack and reset running sign 
 	stack <int> signs;
 	int runningSign = 1;
 	int result = 0;
 	for (int i = 0 ; i < s.size() ; i++) {
 		auto c = s[i];
 		if (c == '('){
 			signs.push(runningSign);
 		}
 		 else if (c == '-'){
 			runningSign = -1 * (!signs.empty() ? signs.top() : 1);
 		}
 		 else if (c == '+') {
 		 	runningSign = 1 * (!signs.empty() ? signs.top() : 1) ;
 		 }  else if ( c== ')' ) {
 		 	signs.pop();
 		 	runningSign = 1;

 		 } else if (isdigit(c)) {
 		 	// numbers
 		 	auto digit = c;
 		 	string digitStr = "";
 		 	while (isdigit(s[i])) {
 		 		digitStr += s[i];
 		 		i++;
 		 	}
 		 	result += runningSign * stoi(digitStr);
 		 	i--;
 		 }
 	}
 	return result;

 }

 int main() {
 	cout << calculate("1 + 1") << endl;
 	cout << calculate("2 - 1 + 2") << endl;

 }