#include <iostream>
#include <string>
#include <cassert>

using namespace std;

string pushDominoes(string dominoes) {
	// Consider the last seen 'L' and also the last seen 'R'
	// If current domino is 'R' and last 'R' > L, then we have R ...R, make everything in between R, update last seen R to here
	// If current domino is 'R'  and last 'R'< L, then we have L....R, do nothing, update last seen R to here
	// If current domino is 'L' and last 'L' > R, then weh ave L....L, make everything L, update last seen L to here
	// If current domino is 'L' and last 'L' < R, then we have R...L, take two pointer solution from both ends and update one at a time, ignore the case, when we reach the mdidle
	// Edge cases for 'L's at the beginning and for 'R's at the end
	int lastR = -1;
	int lastL = -1;
	for (int i = 0; i < dominoes.size(); i++ ) {
		if (dominoes[i] == 'R') {
			if (lastR > lastL) {
				for (int j = lastR + 1; j < i; j++) {
					dominoes[j] = 'R';
				}
			}
			lastR = i;
		} else if (dominoes[i] == 'L') {
			if (lastL > lastR || lastR == -1) {
				for (int j = lastL + 1; j < i; j++) {
					dominoes[j] = 'L';
				}
			} else if (lastL < lastR) {
				int left = lastR + 1;
				int right = i  - 1;
				while (left < right) {
					dominoes[left] = 'R';
					dominoes[right] = 'L';
					left++;
					right--;
				}
				lastR = left - 1;
			}
			lastL = i;
		}

	}
	if (lastR > lastL) {
		lastR++;
		while (lastR < dominoes.size()) {
			dominoes[lastR] = 'R';
			lastR++;
		}
	}
	return dominoes;
}

int main() {
	assert(pushDominoes("RR.L") == "RR.L");
	assert(pushDominoes(".L.R.") == "LL.RR");
	assert(pushDominoes("R...L") == "RR.LL");
	assert(pushDominoes("LL.RR.LLRRLL..") == "LL.RR.LLRRLL..");

}