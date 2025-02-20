#include <iostream>
#include <list>
#include <string>
using namespace std;

class BrowserHistory {
public:
	BrowserHistory(string homepage) {
		update(homepage);

	}

	void visit(string url) {
		// Clear all history after the current pointer
		auto next = current;
		next++;
		history.erase(next, history.end());
		update(url);
	}


	string back(int steps) {
		// Move back x steps
		for (int i = 0; i < steps && (current != history.begin()); i++) {
			current--;
		}
		return *current;
	}

	string forward(int steps) {
		// Move forward x steps
		auto last = history.end();
		last--;
		next()
		for (int i = 0; i < steps && current != last; i++) {
			current++;
		}
		return *current;
	}
private:
	void update(string url) {
		history.push_back(url);
		current = history.end();
		current--;
	}
	std::list<string> history;
	std::list<string>::const_iterator current;

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