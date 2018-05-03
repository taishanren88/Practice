 #include "tree_utils.h"
#include <cassert>

    bool helper(TreeNode* root, long min, long max);
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
   
    bool helper(TreeNode* root, long min, long max)
    {
        if (!root)
            return true;
        if (root->val <= min || root->val >= max)
            return false;
        // If going left, you must be smaller than current node, update maximum
        // If going right, you must be larger than current node, update minimum
        return helper(root->left, min, root->val) && helper(root->right, root->val, max);
    }
    
    int main()
    {
        TreeNode* test = deserialize("1,1,null,null");
        assert(!isValidBST(test));
        
        test = deserialize("2,1,3,null,null,null,null");
        assert(isValidBST(test));
    }
