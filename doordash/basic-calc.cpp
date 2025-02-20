#include <iostream>
#include <deque>
#include <string>
using namespace std;

deque<string> tokenize(std::string line, std::string tokens) {
	deque<string> results;

    std::size_t prev = 0, pos;
    while ((pos = line.find_first_of(tokens, prev)) != std::string::npos)
    {
        if (pos > prev)
            results.push_back(line.substr(prev, pos-prev));
        results.push_back(line.substr(pos, 1));
        prev = pos+1;
    }
    if (prev < line.length())
        results.push_back(line.substr(prev, std::string::npos));
    return results;
}
int main() {
	auto tok1 = tokenize("3+2", "+-/*()");
	assert(tok1.size() == 3 && tok1[0] == "3" && tok1[1] == "+" && tok1[2] == "2");

	auto tok2 = tokenize("6-4/2","+-/*()" );
	assert(tok2.size() == 5 && tok2[0] == "6" 
		&& tok2[1] == "-" && tok2[2] == "4" && tok2[3] == "/" && tok2[4] == "2");

	auto tok3 = tokenize("5 + 5 *2", "+-*");

	tok1 = tokenize("(3+2)", "+-/*()");
	assert(tok1.size() == 5 && tok1[0] == "(" && tok1[1] == "3" && tok1[2] == "+"
			&& tok1[3] == "2" && tok1[4] == ")");
}