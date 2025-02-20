#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

 /* Definition for a binary tree node. */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void preorder(TreeNode* n,int y, int x, map<int,map<int, multiset<int> >>& structure ) {
	if (!n) {
		return;
	}
	structure[x][y].insert(n->val);
	preorder(n->left, y + 1, x -1, structure);
	preorder(n->right, y + 1, x + 1, structure);

}

vector<vector<int>> verticalTraversal(TreeNode* root) {
	// Root node is at (0,0). Left is => (-1,1) . Right is (1, 1)
	// Perform a traversal of the tree
	// Generally: If we go left, take the previous node's position (x) and do x -1
	// Generally If we go right, take the previous node's position (x) and do x + 1 
	// Mark node's current position
	// Maintain a sorted map[x positions] -> [map[y_position1 -> set,map[y_position2 -> set ]
	// Becaus there can be same node at same row and column, we need to sort, so we also need to have a sorted set at each (row, column)
	
	 
	 map<int,map<int, multiset<int> >> structure;
	 preorder(root, 0, 0 , structure);

	 vector<vector<int>> results;
	 for (auto& x_map : structure) {
	 	vector<int> result;
	 	for (auto& y_map : x_map.second) {
	 		for (auto val : y_map.second) {
	 			result.push_back(val);
	 		}
	 	}
	 	results.push_back(result);
	 }
	 return results;
}

int main() {

}