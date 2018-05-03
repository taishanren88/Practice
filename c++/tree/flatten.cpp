#include "tree_utils.h"
#include <cassert>

/**
Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6

*/

// Last visited helps us keep track of the last node we visited. Once we have that, it's right node is the next node in pre-order traversal
void helper(TreeNode* curr, TreeNode*& lastVisited)
{
    if (!curr)
        return;
    if (curr != lastVisited)
    {
        lastVisited->right = curr;
        lastVisited = curr;
    }
    TreeNode* right = curr->right; // save this because we we could potentially update this
    helper(curr->left, lastVisited);
    curr->left = nullptr;
    helper(right, lastVisited);
}

void flatten(TreeNode* root) 
{
    TreeNode* curr = root; // Track the end of the list
    helper(root, curr);
}
/*  g++ flatten.cpp -o flatten -std=c++11*/
int main()
{
    TreeNode* test = deserialize("1,2,5,3,4,null,6");
    flatten(test);
    assert(serialize(test) == "1,null,2,null,3,null,4,null,5,null,6,null,null,");
}
