#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BrowserHistory {
public:
	BrowserHistory(string homepage) {
		history.emplace_back(homepage);
		pos = 0;
	}

	void visit(string url) {
		history.erase(history.begin() + pos + 1, history.end());
		history.emplace_back(url);
		pos = history.size() - 1;
	}

	string back(int steps) {
		pos -= steps;
		if (pos < 0 ) {
			pos = 0;
		}
		return history[pos];
	}

	string forward(int steps) {
		pos += steps;
		if (pos >= history.size()) {
			pos = history.size() - 1;
		}
		return history[pos];
	}
private:
	vector<string> history;
	int pos;
};
int main() {
	BrowserHistory browserHistory ("leetcode.com");
	assert(browserHistory.back(0) == "leetcode.com");
	browserHistory.visit("google.com");
	assert(browserHistory.back(0) == "google.com"
		 && browserHistory.forward(0) == "google.com");
	assert(browserHistory.back(1) == "leetcode.com");
	assert(browserHistory.forward(1) == "google.com");
	browserHistory.visit("facebook.com");
	assert(browserHistory.forward(1) == "facebook.com");

	browserHistory.visit("youtube.com");
    assert(browserHistory.forward(1) == "youtube.com");
    assert(browserHistory.back(1) == "facebook.com");
    assert(browserHistory.back(1) == "google.com");
    assert(browserHistory.forward(1) == "facebook.com");
    browserHistory.visit("linkedin.com");
    assert(browserHistory.forward(2) == "linkedin.com");
     assert(browserHistory.back(2) == "google.com");





}