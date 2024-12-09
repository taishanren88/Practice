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
 
// Encodes a tree to a single string.
string serialize(TreeNode* root) {
	if (root == nullptr) {
		return "null";
	}

   return std::to_string(root->val) +","+ serialize(root->left) + +"," +serialize(root->right);
}



vector<string> makeTokens(string data) {
	 // stringstream class check1 
    stringstream check1(data); 
    string intermediate; 
      
     vector<string> tokens;
    // Tokenizing w.r.t. space ' ' 
    while(getline(check1, intermediate, ',')) { 
        tokens.push_back(intermediate); 
    } 
    return tokens;
}

TreeNode* deserializeHelper( vector<string> tokens, int& pos) {
	if (pos == tokens.size()) {
		return nullptr;
	}
	if (tokens[pos] == "null") {
		pos++;
		return nullptr;
	}
	auto node = new TreeNode(stoi(tokens[pos]));
	pos++;
	node->left = deserializeHelper(tokens,pos);
	node->right = deserializeHelper(tokens,pos);
	return node;
}


// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
	// Tokenize the string into tokens
	// Iterate the array in a pre-order fashion and keep track of current position 
	// Each step of the preorder traversal, iterate the position
	// if we reach the end, w're done
	auto tokenized = makeTokens(data);
	int pos = 0;
    return deserializeHelper(tokenized, pos);
}

int main() {
	auto tokenized = makeTokens ("abc,def,ghi");
	for (string s : tokenized) {
		cout << s << endl;
	}
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	auto dserialized = deserialize("1,2,null,null,3,null,null");
		cout << serialize(dserialized) << endl;

	cout << "here" << endl;
	cout << dserialized->val << endl;
	cout << dserialized->left->val << endl;
	cout << dserialized->right->val << endl;



}