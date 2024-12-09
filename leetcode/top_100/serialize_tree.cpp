#include <iostream>
#include <sstream>
#include <vector>
#include "BinTreeUtils.h"
using namespace std;

/**
You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "1,2, null , null 3,4, ,null, null, 5, null, null"
*/
// Encodes a tree to a single string.
void serializeHelper(TreeNode* curr, std::string& result) {
	if (!result.empty()) {
		result += ",";
	}
	if (curr) {
		result += std::to_string(curr->val);
		serializeHelper(curr->left, result);
		serializeHelper(curr->right, result);
	} else {
		result += "null";
	}
}
string serialize(TreeNode* root) {
    // If we reach a node, append a comma (if string not empty)
    // If we reach null, append "null" with comma
    std::string result;
	serializeHelper(root, result);
	return result;
}

TreeNode* deserializeHelper(vector<string>& input, int& pos ) {
	if (pos >= input.size()) {
		return nullptr;
	} else {
		if (input[pos] == "null") {
			pos++;
			return nullptr;
		} else {
			auto node = new TreeNode(std::stoi(input[pos]));
			pos++;
			node->left=deserializeHelper(input, pos);
			node->right = deserializeHelper(input, pos);
			return node;
		}
	}
}
vector<string> split( const std::string& input, char delim) {
	vector<string> result;
	std::stringstream ss(input);
	std::string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}
// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
	// Consume the array like a pre-order DFS.
	// If we encounter a non-null string, allocate a node and go left,
	// If null return null
	// Process the next node by skipping over the next comma.
	auto tokenized = split(data , ',');
	int pos = 0;
	auto root  = deserializeHelper(tokenized, pos);
	return root;
    
}
int main() {
	auto tree1 = new TreeNode(1);
	tree1->left = new TreeNode(2);
	assert(serialize(tree1) == "1,2,null,null,null");
	auto tree1Deserialized = deserialize("1,2,null,null,null");
	assert(tree1Deserialized->val == 1);
	assert(tree1Deserialized->right == nullptr);
	assert(tree1Deserialized->left->val == 2);
	assert(tree1Deserialized->left->left == nullptr);
	assert(tree1Deserialized->left->right == nullptr);


	auto tree2 = deserialize("1,2,null,null,3,4,null,null,5,null,null");
	assert(tree2->val == 1);
	assert(tree2->left->val == 2);
	assert(tree2->left->left == nullptr);
	assert(tree2->left->right == nullptr);
	assert(tree2->right->val == 3);
	assert(tree2->right->left->val == 4);
	assert(tree2->right->right->val == 5);
	assert(tree2->right->right->left == nullptr);
	assert(tree2->right->right->right == nullptr);
}