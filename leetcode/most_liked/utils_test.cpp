#include <iostream>
#include "utils.h"
#include <vector>

using namespace std;
int main () {
	// String tokenize
	assert(tokenize("fooblah,", ",", true) == vector<string>({"fooblah", ","}));
	assert(tokenize("fooblah", ",", true) == vector<string>({"fooblah"}));
	assert(tokenize("foo,blah", ",", true) == vector<string>({"foo", ",", "blah"}));
	assert(tokenize("foo,bar,blah", ",", true) == vector<string>({"foo", ",", "bar", ",", "blah"}));
	assert(tokenize("fooblah,", ",", false) == vector<string>({"fooblah"}));
	// Test multiple tokens
	 assert(tokenize("3[a]2[bc]", "[]", false) == vector<string>({"3",  "a", "2",  "bc" }));
	 assert(tokenize("2[abc]3[cd]e", "[]", false) == vector<string>({"2",  "abc", "3",  "cd", "e" }));
	// List utils
	assert(toVector(toList({1})) == vector<int>({1}));
    assert(toVector(toList({})) == vector<int>({}));
    assert(toVector(toList({1,2})) == vector<int>({1,2}));
    assert(toVector(toList({1,2, 3})) == vector<int>({1,2,3}));
}