#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

void dfs(vector<char>& input, int current,vector<char>& path, vector<vector<char>>& results) {
	if (current == input.size()) {
		results.push_back(path);
		return;
	}

	for (int i = current; i < input.size(); i++) {
		path.push_back(input[i]);
	 	swap(input[current], input[i]);
		dfs(input , current + 1, path, results);
	 	swap(input[current], input[i]);
		path.pop_back();
	}
}

vector<vector<char>> getPermutations(queue<char> input) {
		// convert to vector
	vector<char> copyAsVector;
	while (!input.empty()) {
		auto front = input.front();
		input.pop();
		copyAsVector.push_back(front);
	}
	vector<vector<char>> results;
	vector<char> path;
	 dfs(copyAsVector, 0,  path, results);
	 return results;
}

vector<char> joinPath(vector<char>a, vector<char>b ) {
	vector<char> result;
	for (auto n : a) {
		result.push_back(n);
	}
	for (auto n : b) {
		result.push_back(n);
	}
	return result;
}

vector<vector<char>> test(unordered_map<char, vector<char>>& dependencyMap) {
	unordered_map<char, vector<char>> outgoing;
	unordered_map<char, int> incoming;
	for (auto& kv: dependencyMap) {
		auto to = kv.first;
		incoming[to] = kv.second.size();
		for (auto& from : kv.second) {
			if (outgoing.find(from) == outgoing.end()) {
				outgoing[from] = vector<char>();
			}
			outgoing[from].push_back(to);
		}
	}
	queue<char> todo;
	auto getNext =[&]() {
		for (auto& kv : incoming) {
			if (kv.second == 0) {
				todo.push(kv.first);
			}
		}
	};

	getNext();
	vector<vector<char>> results;
	results.push_back(vector<char>());

	using Path = vector<char>;
	vector<Path> possiblePaths;
	while (!todo.empty()) {
		auto len = todo.size();
		auto permutations = getPermutations(todo);
		vector<vector<char>> newResults;
		for (auto& permutation : permutations) {
			for (auto& possiblePath : results) {
				auto res  = joinPath(possiblePath, permutation );
				newResults.push_back(res);
			}
		}
		results = std::move(newResults);
		for (int i = 0; i < len; i++) {
			auto front = todo.front();
			todo.pop();
			for (auto& outgoingNode : outgoing[front]) {
				incoming[outgoingNode]--;
				if (incoming[outgoingNode] == 0) {
					todo.push(outgoingNode);
				}
			}
		}
	}
	return results;
}

int main() {

	queue<char> testPermutationQueue;

	testPermutationQueue.push('A');
    testPermutationQueue.push('B');
    testPermutationQueue.push('C');
	auto res = getPermutations(testPermutationQueue);
	// for (auto& r : res ) {
	// 	for (auto node : r) {
	// 		cout << node<< ",";
	// 	}
	// 	cout << endl;
	// }
	unordered_map<char, vector<char>> dependencyMap;
	dependencyMap['E'] = {'B', 'D'};
	dependencyMap['D'] = {'B', 'C'};
	dependencyMap['C'] = {'A'};
	dependencyMap['B'] = {'A'};
	dependencyMap['A'] = {};
	dependencyMap['F'] = {};
	auto result = test(dependencyMap);
	for (auto c : result) {
		for (auto n : c) {
			cout << n << ",";
		}
		cout << endl;
	}
}