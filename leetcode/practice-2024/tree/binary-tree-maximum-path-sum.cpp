#include <iostream>
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

int maxPathSumHelper(TreeNode* root, int& runningMax){
	if (root == nullptr) {
		return 0;
	}
	int left = maxPathSumHelper(root->left, runningMax);
	if (left < 0 ) {
		left = 0;
	}
	int right = maxPathSumHelper(root->right, runningMax);
	if (right < 0 ) {
		right = 0;
	}
	auto sum = left + right + root->val;
	runningMax = max(sum, runningMax);
	return max(left, right) + root->val;
}
int maxPathSum(TreeNode* root) {
    // maximum path sum is sum of left + sum of right + sum of current
    // If any path is negative exclude it (it can't help us)
    // at any point mark the remaining total
    int globalMax = INT_MIN;
     maxPathSumHelper(root, globalMax);
     return globalMax;
}
int main() {
	TreeNode* root = new TreeNode(2);
	 root->left = new TreeNode(1);
	 root->right = new TreeNode(3);
   cout << maxPathSum (root) << endl;

}