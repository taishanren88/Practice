#include <iostream>
#include <vector>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
} ;

/*
* Convert BFs traversal of tree nodes to tree
*/ 
TreeNode* toTree(std::vector<std::string> input) {
	std::vector<TreeNode*> nodes;
	for (int i = 0; i < input.size() ; i++) {
		if (input[i] != "null") {
			nodes.push_back(new TreeNode(stoi(input[i])));
		} else {
			nodes.push_back(nullptr);
		}
	}
	int nextChild = 1;
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]) {
			if (nextChild < nodes.size()) {
				nodes[i]->left = nodes[nextChild++];
			}
			if (nextChild < nodes.size()) {
				nodes[i]->right = nodes[nextChild++];
			}
		}
	}
	return !nodes.empty() ? nodes[0] : nullptr;
}