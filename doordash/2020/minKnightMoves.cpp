#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

/**
Return true if found in other queue visited, false otherwise
*/
bool bfs(unordered_set<string>& currentVisited, unordered_set<string>& otherVisited,
		 queue<pair<int,int>>& todo) {
	static const vector<pair<int, int>> directions =  { { -2, 1}, { -1, 2}, {1, 2}, {2, 1}, {2, -1} , {1, -2} , { -2, -1}, { -1, -2} };
	auto len = todo.size();
	for (int i = 0; i < len ; i++) {
		auto current = todo.front();
		todo.pop();
		auto positionAsStr= to_string(current.first) +',' + to_string(current.second);
		if (otherVisited.find(positionAsStr) != otherVisited.end()) {
			return true;
		}
		for (auto& dir : directions ) {
			auto next = make_pair(current.first + dir.first, current.second + dir.second);
			auto nextAsStr = to_string(next.first) + ',' + to_string(next.second);
			if (currentVisited.find(nextAsStr) == currentVisited.end()) {
				todo.push(next);
				currentVisited.insert(nextAsStr);
			}
		}
	}
	return false;
}

int minKnightMoves(int x, int y) {
	queue<pair<int, int>> todoFromSrc;
	queue<pair<int, int>> todoFromDst;
	todoFromSrc.push(make_pair(0, 0));
	todoFromDst.push(make_pair(x,y));
	unordered_set<string> visitedSrcToDst, visitedDstToSrc;
	visitedSrcToDst.insert(to_string(0) + ',' + to_string(0));
	visitedDstToSrc.insert(to_string(x) + ',' + to_string(y));
	int minStepsSrcToDst = 0;
	int minStepsDstToSrc = 0;

	while (true) {
		auto resultFromSrc = bfs(visitedSrcToDst, visitedDstToSrc, todoFromSrc);
		if (resultFromSrc) {
			return minStepsSrcToDst + minStepsDstToSrc;
		}
		minStepsSrcToDst++;
		auto resultFromDst = bfs(visitedDstToSrc, visitedSrcToDst, todoFromDst);
		if (resultFromDst) {
			return minStepsSrcToDst + minStepsDstToSrc;
		}
		minStepsDstToSrc++;
	}
	return -1;
}

int main() {
	assert(minKnightMoves(2, 1)  == 1);
	assert(minKnightMoves(5, 5) == 4);
	assert(minKnightMoves(148, 62) == 74);
}