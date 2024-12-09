#include <iostream>
#include "BinTreeUtils.h"
using namespace std;

class SpecialTreeNode {

public: 
	SpecialTreeNode(int aVal) 
	:smallerThan (0) , val(aVal) {

	}
	int smallerThan;
	int val;
	SpecialTreeNode*  left = nullptr;
	SpecialTreeNode*  right = nullptr;

};


/**
Return special node for this node and total number of nodes starting here
*/
pair<SpecialTreeNode*, int> buildSpecialTreeHelper(TreeNode* root) {
	if (!root) {
		return make_pair(nullptr,0);
	} else {
		auto newNode = new SpecialTreeNode(root->val);
		auto leftResult = buildSpecialTreeHelper(root->left);
		auto rightResult = buildSpecialTreeHelper(root->right);
		newNode->smallerThan = leftResult.second;
		newNode->left = leftResult.first;
		newNode->right = rightResult.first;
		return make_pair(newNode, leftResult.second + rightResult.second + 1);
	}
}

SpecialTreeNode* buildSpecialTree(TreeNode* root) {
	auto result = buildSpecialTreeHelper(root);
	return result.first;
}

int find(SpecialTreeNode* root, int numSmallerThan) {
	if (root->smallerThan == numSmallerThan) {
		return root->val;
	} else if (numSmallerThan < root->smallerThan) {
		return find(root->left, numSmallerThan);
	} else {
		return find(root->right, numSmallerThan - (root->smallerThan + 1) );
	}
}

int kthSmallest(TreeNode* root, int k) {
    // Build a special tree. For each node, consider how many nodes are smaller than it
    // Next binary search the node. If numSmallerThan < current node's smaller than ,
    //  keep looking left ( need to get smaller)
    // If k == current node's smaller than , remove existing node and those on the left (numSmallerThan - 1-  k)
    // For a given 'k' smallest, we want k - 1 smaller nodes
    auto specialTree = buildSpecialTree(root);
    return find(specialTree, k -1);
}

void testPrintTree(TreeNode* tree){
	if (!tree ) {
		return;
	}
	cout << tree->val << ",";
	testPrintTree(tree->left);
	testPrintTree(tree->right);
}

void testPrintSpecialTree(SpecialTreeNode* tree){
	if (!tree ) {
		return;
	}
	cout << tree->smallerThan << ",";
	testPrintSpecialTree(tree->left);
	testPrintSpecialTree(tree->right);
}

int main() {
	vector<std::string> treeAsStr = {"3","1","4","null","2"};
	auto tree = toTree(treeAsStr);
	// testPrintTree(tree);
	auto specialTree = buildSpecialTree(tree);
	testPrintSpecialTree(specialTree);
	assert(kthSmallest(tree, 1) == 1);

	treeAsStr = {"5", "3","6","2","4","null","null", "1"};
	tree = toTree(treeAsStr);
	assert(kthSmallest(tree, 3) == 3);

}