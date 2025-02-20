#include <iostream>
#include <deque>
#include <vector>

using namespace std;

deque<string> tokenize(string s, string tokens) {
	string swap = s;
	s = "";
	for (auto c : swap) {
		if (c != ' ') {
			s += c;
		}
	}

	deque<string> results;
	// int last = 0;
	// for (int i = 0; i < s.size(); i++) {
	// 	string digit;
	// 	while (i < s.size()
	// 			&& isdigit(s[i])) {
	// 		digit += s[i];
	// 		i++;
	// 	}
	// 	if (!digit.empty()) {
	// 		results.push_back(digit);
	// 	}
	// 	if (i == s.size()) {
	// 		break;
	// 	}
	// 	if (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '/'
	// 		|| s[i] == '+' || s[i] == '-') {
	// 		results.push_back(string(1, s[i]));
	// 	}
	// }
	std::size_t prev = 0, pos;
    while ((pos = s.find_first_of(tokens, prev)) != std::string::npos)
    {
        if (pos > prev)
            results.push_back(s.substr(prev, pos-prev));
        results.push_back(s.substr(pos, 1));
        prev = pos+1;
    }
    if (prev < s.length())
        results.push_back(s.substr(prev, std::string::npos));
    return results;
}

int calculateFlat(deque<string>& intermediate) {
	// ignore + 
	// transform - to "+"
	// * or / -> take previous and next
	// add upe verything else
	vector<long>  results;
	while (!intermediate.empty()) {
		auto element = intermediate.front();
		intermediate.pop_front();
		if (element == "+") {
		}
		 else if (element == "-"){
		 results.push_back(-1 * stol(intermediate.front()));
		 intermediate.pop_front();
		 }
		 else if (element == "*") {
		 	results.back() *= stol(intermediate.front());
		 	intermediate.pop_front();
		 }
		 else if (element == "/") {
		 	results.back() /= stol(intermediate.front());
		 	intermediate.pop_front();
		 } else {
		 	results.push_back(stol(element));
		 }
	}
	int sum = 0;
	for (auto n : results) {
		sum += n;
	}
	return sum;
}

void helper(deque<string>& toprocess) {
	deque<string> intermediate;
	while (!toprocess.empty() 
			&& toprocess.back() != "(") {
		auto element = toprocess.back();
		toprocess.pop_back();
		intermediate.push_front(element);
	}

	if (!toprocess.empty()
		&& toprocess.back() == "(") {
		toprocess.pop_back();
	}

	auto result = calculateFlat(intermediate);
	toprocess.push_back(to_string(result));
}

int calculate(string s) {
    // Handle the same way as Basic Calculator- I
    // Tokenize based off +, - , *, '/'
    // Process it via a -2 pass algoirthm, where we ignore all processing, but parentheses
    // If we hit an open parentheses, add everything until we hit a right prentheses
    // If so, pop everything off into a a separate vector,  until the first parentheses, then process these  independent, get the result andput it back
    // By the end of the first pass, guarantee no more parentheses
    // process the result of that indendently
    // use de-queue for all intermediate results, since wnt the flexibility of both stack and queue
    
    auto toprocess = tokenize(s, "+-/*()");
    deque <string>intermediate;
    while (!toprocess.empty()) {
    	auto element = toprocess.front();
    	toprocess.pop_front();
    	if (element == ")") {
    		helper(intermediate);
    	} else {
    		intermediate.push_back(element);
    	}
    }

    // 2nd pass
 	auto result = calculateFlat(intermediate);
    return result;
}

int main() {
	auto tok1 = tokenize("3+2", "+-/*()");
	assert(tok1.size() == 3 && tok1[0] == "3" && tok1[1] == "+" && tok1[2] == "2");

	helper(tok1);
	assert(tok1.back() == "5");

	auto tok2 = tokenize("6-4 / 2 ","+-/*()" );
	assert(tok2.size() == 5 && tok2[0] == "6" && tok2[1] == "-" && tok2[2] == "4" && tok2[3] == "/" && tok2[4] == "2");
	helper(tok2);
	assert(tok2.back() == "4");

	auto tok3 = tokenize("5 + 5 *2", "+-*");
	helper(tok3);
	assert(tok3.back() == "15");

	tok1 = tokenize("(3+2)", "+-/*()");
	assert(tok1.back() == ")");
	tok1.pop_back();
	helper(tok1);
	assert(tok1.back() == "5");
	assert(calculate("1 + 1") == 2);
	assert(calculate("6 -4 / 2") == 4);


	assert(calculate("2*(5+5*2)/3") == 10);
	assert(calculate("2*(5+5*2)/3 + (6/2+8)") == 21);
	assert(calculate("(2+6* 3+5- (3*14/7+2)*5)+3")== -12);
	assert(calculate("0-2147483648") == -2147483648);
}