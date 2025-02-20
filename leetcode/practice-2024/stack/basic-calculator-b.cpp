#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

int calculate(string s) {
    // tokenize: remove the spaces
    // keep track of current sign
    // // If we encounter a -, running sign is stack top * -1
    // if we encounter a '(', push current sign to sign stack
    // if we encounter a ')', pop current sign from sign stack and ereset current sign to 1
	// if we encounter a number, push the number to numbers stack * current sign

    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
	stack <int> signs;
	stack <int> numbers;
	int currentSign  = 1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			signs.push(currentSign);
		} else if (s[i] == ')') {
			signs.pop();
			currentSign = 1;
		} else  if (s[i] == '+') {

		} else if (s[i] == '-') {
			currentSign *= signs.empty() ? -1 : signs.top();
		} else if (isdigit(s[i])) {
			std::string digitStr;
			while (isdigit(s[i])){
				digitStr += s[i];
				i++;
			}	
			numbers.push(currentSign* stoi(digitStr));
			i--;
		}
	}
	int result = 0;
	while (!numbers.empty()) {
		auto top = numbers.top();
		numbers.pop();
		result += top;
	}
	return result;
}

int main() {

}