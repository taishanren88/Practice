    // 1st Level -> 0 -> 2^0 = 1
    // 2nd Level -> 0, 1 -> 2^0 + 2^1 = 3
    // 3rd level -> 0, 1, 2 -> 2^0 + 2^1 + 2^2 = 7
    // Observe: Eliminating half the nodes, essentailly removes half the nodes each time
    
    // Returns the height in terms of levels going left.
    // No nodes -> means 0 levels, 1 node -> 1 level, 3 nodes -> 2 
    int height(TreeNode* node)
    {
        if (!node)
            return 0;
        return 1 + height(node->left);
    }
    // Get the height of the left subtree
    // Get the height of the right subtree
    // If they are the same, transition is in the right subtree. Exclude the full left subtree but count its nodes
    // If they are different, transition is in the left subtree
    int countNodes(TreeNode* node) {
        if (!node)
            return 0;
        // Note: Theoretically we should use height -1 for height of subtree, but by using height we include current node as well
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        if (leftHeight == rightHeight) // exclude full left subtree
            return countNodes(node->right) + pow (2,leftHeight - 1);
        else  // leftHeight < rightHeight, transition in left, excldue full right subtree
            return countNodes(node->left) + pow(2, rightHeight -1);
    }
