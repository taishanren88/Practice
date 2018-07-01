  /**
  Given a binary tree, write a function to get the maximum width of the given tree. The width of a tree is the maximum width among all levels. The binary tree has the same structure as a full binary tree, but some nodes are null.

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
  
            /*
        Ex 1:
          1 
         /   \
        3     2 
       / \   /  \  
      5   3  x  9 
      
     i: [0 1 2 3 4. 5    6]
     arr: [1,3,2,5,3, null, 9]
      
          1
         /  
        3
       / \
      5   3
       i:   0  1   2     3  4
       arr: [1, 3, null, 5, 3]
      
      
          1 
         / \
 [1]   3   2   [2]
       /     \  
 [3]  5 x  x   9  [6]
     /           \
[7] 6 x xx xx  x  7 [14]

    i:   0 ...     3            ...  7   ...           14
    arr: [1, 3, 2, 5, null ,null, 9, 6, null,..., null, 7]
    
        */
    int widthOfBinaryTree(TreeNode* root) {
        // Consider the binary tree as a deserialized array with all nodes. Each index is calculated from its parent
        // We know that for a node at index i , its children are at 2*i + 1 , and 2 * i + 2
        vector<tuple<int,int>> distances;
        preOrderHelper(root, 0, 0, distances);
        int maxWidth = 0;
        for (const auto& distance: distances)
        {
            maxWidth = max(maxWidth,get<1>(distance) - get<0>(distance) + 1);
        }
        return maxWidth;
    }
    void preOrderHelper(TreeNode* root, int level, int index, vector<tuple<int,int>>& distances /* [minIndex, maxIndex] of each level*/)
    {
        if (!root)
            return;
        if (level == distances.size()) // first time encountering here, it's a leftmost node
        {
            distances.push_back(make_tuple(index, index));
        }
        else
        {
           // get<1>(nodes[level]) = index; // works via move semantics
            auto currTup = distances[level];
            distances[level] = make_tuple(get<0>(currTup), index);
        }
        
        preOrderHelper(root->left, level + 1, 2 *index + 1, distances);
        preOrderHelper(root->right, level + 1, 2 * index + 2, distances);
    }
    
