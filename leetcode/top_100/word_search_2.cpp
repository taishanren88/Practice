#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class TrieNode
{
public:
	TrieNode()
		: children(26, nullptr), endsHere(false) {

	}
	bool endsHere;
	vector<TrieNode*> children;
};

class Trie {

public:
	Trie(vector<string>& dict) {
		root = new TrieNode();
		for (auto word : dict) {
			TrieNode* curr = root;
			for (char c : word) {
				int index = c - 'a';
				if (!curr->children[index]) {
					curr->children[index] = new TrieNode();
				}
				curr = curr->children[index];
			}
			curr->endsHere = true;
		}
	}

	bool startsWith(string word) const {
		auto result = contains(word);
		return result != nullptr;
	}
	bool endsHere(string word, TrieNode*& output) const {
		auto result = contains(word);
		output = result;
		return result != nullptr && result->endsHere;
	}

	TrieNode* root;
private:
	TrieNode* contains(string word )  const {
		TrieNode* curr = root;
		for (char c : word) {
			int index = c - 'a';
			if (!curr->children[index]) {
				return nullptr;
			}
			curr = curr->children[index];
		}
		return curr;

	}
};


void dfs(vector<vector<char>>& board, int r, int c, std::string curr, const Trie& trie, unordered_set<string>& results) {
	constexpr const char VISITED = '\0';
	if (r < 0 || r >= board.size()
	        || c < 0 || c >= board[r].size()) {
		return;
	}
	if (board[r][c] == VISITED) {
		return;
	}
	std::string potential = curr + board[r][c];
	TrieNode* output;
	if (trie.endsHere(potential, output)) {
		results.insert(potential);
		output->endsHere = false; // remove duplicates
	}
	if (trie.startsWith(potential)) {
		char original = board[r][c];
		board[r][c] = VISITED;
		dfs(board, r - 1 , c, potential, trie, results);
		dfs(board, r + 1 , c, potential, trie, results);
		dfs(board, r , c - 1, potential, trie, results);
		dfs(board, r , c + 1, potential, trie, results);
		board[r][c] = original;
	}
}
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
	// Build a trie from the dictionary
	// After building the trie, do a DFS from every position of the board
	// and check if a valid word is found if so add it to the list of results
	Trie trie (words);

	 unordered_set<string> results;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			 dfs(board, i , j, "", trie, results);
		}
	}

	return vector<string>(results.begin(), results.end());
}

int main() {
	vector<string> dict = {"oath", "pea", "eat", "rain"};
	Trie trie(dict);
	TrieNode* dummy;
	assert(trie.startsWith("oa"));
	assert(trie.startsWith("oath"));
	assert(!trie.endsHere("oa", dummy));
	assert(trie.endsHere("oath", dummy));
	assert(trie.endsHere("pea", dummy));
	assert(trie.startsWith("p"));
	assert(!trie.startsWith("x"));
	assert(!trie.startsWith("bat")); // doesn'te xist
	assert(!trie.endsHere("bat", dummy)); // doesn'te xist

	vector<vector<char>> board = {
		{'o', 'a', 'a', 'n'},
		{'e', 't', 'a', 'e'},
		{'i', 'h', 'k', 'r'},
		{'i', 'f', 'l', 'v'}
	};
	 auto res = findWords(board, dict);
	 sort(res.begin(), res.end());
	 assert(res[0] == "eat" && res[1] == "oath");

	 vector<vector<char>> board2 = {
		{'a', 'a'}
	};
	dict = {"a"};
	res = findWords(board2, dict);
	 sort(res.begin(), res.end());
	 assert(res[0] == "a" && res.size() == 1);
}