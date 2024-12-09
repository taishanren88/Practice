#include <iostream>
#include "BinTreeUtils.h"
using namespace std;

bool isValidBSTHelper(TreeNode* curr, long min, long max) {
	if (!curr) {
		return true;
	}
	if (curr->val <= min || curr->val >= max) {
		return false;
	} else {
		return isValidBSTHelper(curr->left, min, curr->val)
			&& isValidBSTHelper(curr->right, curr->val, max);
	}
}
bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}

int main() {
	vector<std::string> input = {"2", "1", "3",};
	auto tree1 = toTree(input);
	assert(isValidBST(tree1));

	input = {"5", "1", "4", "null", "null", "3", "6"};
	auto tree2 = toTree(input);
	assert(!isValidBST(tree2));

	input = {"1", "1"};
	auto tree3 = toTree(input);
	assert(!isValidBST(tree2));
}