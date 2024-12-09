#include <iostream>
#include <vector>
#include <stack>

using namespace std;


struct TreeNode {
	TreeNode() {
		left = nullptr;
		right = nullptr;
	}
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<int> inorderTraversal(TreeNode* root) {
// To do an iterative in order traversal,
//  we need to go as far left as we can to get the smallest node
//  Use a stack to track things as we go
//  If "curr" pointer is null, then pop from the stack
//  If there's a valid right element, set curr to that

	stack<TreeNode*> node_stack;
	auto curr = root;
	vector<int> results;
	while (curr || !node_stack.empty()) {
		if (curr) {
			node_stack.push(curr);
			curr = curr->left;
		} else {
			auto top = node_stack.top();
			node_stack.pop();
			results.push_back(top->val);
			if (top->right) {
				curr = top->right;
			}
		}
	}
	return results;

}

int main() {
	TreeNode* root = new TreeNode(2);
	root->left = new TreeNode(1);
	root->right = new TreeNode(3);
	auto res = inorderTraversal(root);
	for ( auto n : res) {
		cout << n << endl;
	}
}