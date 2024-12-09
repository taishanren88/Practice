#include <iostream>
#include <vector>
#include <sstream>
#include <queue>

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
 
//  void kthSmallestHelper(TreeNode* root, std::priority_queue<int, vector<int>, greater<int>>& minHeap) {
//   if (root == nullptr) {
//     return;
//   }
//   minHeap.push(root->val);
//   kthSmallestHelper(root->left, minHeap);
//   kthSmallestHelper(root->right, minHeap);
//  }
//    int kthSmallest(TreeNode* root, int k) {
//     // iterate over entire tree 
//     // build a minheap
//     std::priority_queue<int, vector<int>, greater<int>> minHeap;
//     kthSmallestHelper(root, minHeap);

//     for (int i = 1; i < k; i ++) {

//       minHeap.pop();
//     }
//     return minHeap.top();
// }
// 
// 
TreeNode* buildOrderedTree(TreeNode* root) {
  if (root == nullptr) {
    return nullptr;
  }
  auto node = buildOrderedTree(root->left);
  auto newNode = new TreeNode(root->val);
}
int kthSmallest(TreeNode* root, int k) {
  // pre-process: build a special tree where we do an in-order traversal
  // post-process: pre-order traversal. if k == 0 , we are good
}

int main() {
	TreeNode* root = new TreeNode(2);
	 root->left = new TreeNode(1);
	 root->right = new TreeNode(3);
   cout << kthSmallest (root, 1) << endl;
      cout << kthSmallest (root, 2) << endl;
}