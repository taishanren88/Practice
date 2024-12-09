#include <iostream>
#include <vector>
#include <sstream>

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
 
 bool isValidBSTHelper(TreeNode* root, long min, long max) {
	// At each point, we have an allowable range
	// If we go left, it means that the new range has to be smaller (MAX - 1) . BST left is always smaller 
	// If we go , right means that the new rang has to be larger (MIN + 1) . BST right is always larger 
    if (root == nullptr) {
    	return true;
    }
    if (root->val < min || root->val > max) {
    	cout << "HERE" << "[" << std::to_string(min) << "," << std::to_string(max) << "], " << std::to_string(root->val) <<  endl;
		return false;
	}
	return isValidBSTHelper(root->left, min, (long)root->val - 1) 
	&& isValidBSTHelper(root->right, (long) root->val + 1, max);
}


bool isValidBST(TreeNode* root) {
	// At each point, we have an allowable range
	// If we go left, it means that the new range has to be smaller (MAX - 1) . BST left is always smaller 
	// If we go , right means that the new rang has to be larger (MIN + 1) . BST right is always larger 
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}

int main() {
	TreeNode* root = new TreeNode(2);
	 root->left = new TreeNode(1);
	 root->right = new TreeNode(3);
	cout << isValidBST(root) << endl;

}