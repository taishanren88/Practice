#include <iostream>
#include <deque>
#include <string>
using namespace std;

deque<string> tokenize(std::string s) {
	// remove spaces
	string swap = s;
	s = "";
	for (auto c : swap) {
		if (c != ' ' )
			s += c;
	}

	deque<string> tokens;
	for (int i = 0; i < s.size(); i++) {
		string digit;
		while (i < s.size() && isdigit(s[i])) {
			digit += s[i];
			i++;
		}
		if (!digit.empty()) {
			tokens.push_back(digit);
		}
		if (s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			tokens.push_back(string(1, s[i]));
		}
	}
	return tokens;
}

long calculateSimple(deque<string> tokens) {
	deque<long> results;
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i] == "+") {

		} else if (tokens[i] == "-") {
			results.push_back(-1 * stol(tokens[i+1]));
			i++;
		} else if (tokens[i] == "*") {
			results.back() *= stol(tokens[i+1]);	
			i++;
		} else if (tokens[i] == "/") {
			results.back() /= stol(tokens[i+1]);
			i++;
		} else {
			results.push_back(stol(tokens[i]));
		}
	}
	long sum = 0;
	for (auto n : results) {
		sum += n;
	}
	return sum;
}
int calculate(string s) {
    // Tokenize the string into a double-ended queue
    // Provide a function to be able to calculate a simple double-ended queue of tokens and their result
    // Fist pass : push evrything on. If encounter ')', create intermediary dequeu until encounter ( , which also get popped. Push result back
    // Secon pass : eerythig is simple tokens now. Give to function as above
	auto tokens = tokenize(s);
	deque<string> intermediary;
	while (!tokens.empty()) {
		auto token = tokens.front();
		tokens.pop_front();
		if (token == ")") {
			string tmpToken;
			deque<string> tmp;
			while ((tmpToken = intermediary.back()) != "(") {
					intermediary.pop_back();
					tmp.push_front(tmpToken);
				}
				intermediary.pop_back();
				intermediary.push_back(std::to_string(calculateSimple(tmp)));
		}
		else {
			intermediary.push_back(token);
		}

	}

	auto result = calculateSimple(intermediary);
	return result;
}

int main() {
	assert (tokenize(" 1 + 1 ").size() == 3);
	assert (tokenize(" 6 - 4 / 2 ").size() == 5);
	assert (tokenize("2*(5+5*2)").size() == 9);
	assert (tokenize("2*(5+5*2)/3+(6/2+8)").size() == 19);

	assert(calculate("1 +1") == 2);
	assert(calculate("6 - 4 / 2") == 4);
	assert(calculate("2*(5+5*2)/3+(6/2+8)") == 21);
	assert(calculate("(2+6 *3+5 - (3*14/7+2) * 5) +3") == -12);

}