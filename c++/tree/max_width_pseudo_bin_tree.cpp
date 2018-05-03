/*Given a binary tree, write a function to get the maximum width of the given tree. The width of a tree is the maximum width among all levels. The binary tree has the same structure as a full binary tree, but some nodes are null.

The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).

*/   
   
    /* Because it's given that this tree is like a FULL binary tree, with some missing nodes replaced by nullptr. Therefore
       we know for sure that a node's subchildren will be 2*index + 1 and 2*index + 2, where 0 is the first index
       Soln: Map level ->[minimum, maximum] , and keep track of max height
       */
    int widthOfBinaryTree(TreeNode* root) {
        vector<tuple<int,int>> level2Range;
        int runningMax = 0;
        helper(root, 0, 0, level2Range, runningMax);
        return runningMax;
    }
    
    void helper(TreeNode* node, int currIndex, int currLevel, vector<tuple<int,int>>& level2Range, int& oRunningMax)
    {
        if (!node)
            return;
        if (currLevel == level2Range.size())  // First node at this level
        {
            level2Range.push_back(make_tuple(currIndex, currIndex));
            oRunningMax = max(1, oRunningMax);
        }
        else
        {
            auto& currentRange = level2Range[currLevel];
            get<1>(currentRange) = currIndex; // Update the maximum
            oRunningMax = max(currIndex - get<0>(currentRange) +1, oRunningMax);
        }
        // preorder-recurse
        helper(node->left, 2 * currIndex + 1, currLevel +1, level2Range, oRunningMax);
        helper(node->right, 2 * currIndex + 2, currLevel +1, level2Range, oRunningMax);
    }
