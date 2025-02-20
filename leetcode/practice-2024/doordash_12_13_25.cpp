#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/**
Given a binary tree, find the maximum path sum from any two "alive nodes" within the tree. We can assume a node is an alive node if and only if it is a leaf node, indicated by an asterisk below.

Example 1

Input

             5
           /    \  
         2       0 
        /       /  \
      *25      *14  *15
Output:

47 = 25 + 2 + 5 + 15
Example 2

Input

             5
           /    \  
         2       0 
        /  \     / \
      *100 *50  *4 *15
Output:

152 = 100 + 2 + 50

100* - 2 - 5 - 0 - 15* --> 122


Input

             5
           /    \  
         2       0 
        /  \     / \
      *100 50  *4   *15
      

      
        
      
Output: 


Notes: 
// 
*/

// int addNumbers(int a, int b) {
//     return a+b;
// }

/**
EXTENSION 
----------
What if the tree we are given can have "alive nodes" at non-leaf nodes as well? Find the maximum path between any two alive nodes within the tree. A maximum path may only have the two alive nodes without any other alive nodes in between. For example the alive nodes are highlighted with asterisks.

Input

             5
           /    \  
         2*       0 
        /  \     / \
      100*  50* 4*  15*
      
      
              5
           /    \  
         *40       0 
        /  \     / \
      100*  50* 50*  300*
Output:
300 + 4=> 400

4* - 5 - 0 - 300*
4* - 5 - 0 - 100*
50* - 0 - 300*
4* - 100*
4* - 50*

We can see we don't include 50 here because 2* is an alive node and must be at the end of a path.
100 + 2 = 102

// 2 things we think:
1. set maximum_value : If current node is alive => set the maximum value -> max(left + curr_val, right + curr_val)
2. Propagate what : if current node is alive : 2 
*/



const int INVALID = -1000;
struct Node {
  public:
  Node(int v):left(nullptr),right(nullptr), val(v) {
      
  }  
  // Empty constructor
  Node() :left(nullptr), right(nullptr){
      
  }
    Node* left;
    Node* right;
    int val;
    
};


int helper(Node* root, int& maxValue) {
    // empty node
    if (!root) {
        return INVALID;
    }
    // check for leaf node 
    auto left =  helper(root->left, maxValue);
    auto right = helper(root->right, maxValue);
    if (left == INVALID && right == INVALID) { // leaf node
        return root->val;
    }
    printf("Running max : %d, left : %d, right :%d\n", maxValue,  left, right);
    if (left != INVALID && right != INVALID) {
        maxValue = max(maxValue, left + right + root->val);
    }

    return max(left, right) + root->val;
    /*
    Input

                5
            /    \  
            2       0 
            /       /  \
        *25      *14  *15
    Output:

    47 = 25 + 2 + 5 + 15
    */
    
    // not a leaf node 
    // Leaf Nodes -> Return an actual value
    // Not a leaf node ->  return the max(left, right), but only if we had values > -INFINITY 
    // Any non-leaf node -> capture the maxiimum value that we can return as a result + current node's value 
    // At any point, we can only return the maximum going through one path , because there could be another path from another branch 
}

int findMaximumPathSum(Node* root) {
    int result = INVALID;
     helper(root, result);
     return result;
}


struct NodeSpecial {
  public:
  NodeSpecial(int v, bool a): left(nullptr),right(nullptr), val(v), alive(a) {}  
  // Empty constructor
  NodeSpecial() :left(nullptr), right(nullptr), alive(false){
      
  }
    NodeSpecial* left;
    NodeSpecial* right;
    int val;
    bool alive;
};


int helperSpecial(NodeSpecial* root, int& maxValue) {
    // empty node
    if (!root) {
        return INVALID;
    }
    // check for leaf node 
    auto left =  helperSpecial(root->left, maxValue);
    auto right = helperSpecial(root->right, maxValue);
    if (left == INVALID && right == INVALID) { // leaf node
        return root->val;
    }
    // printf("Running max : %d, left : %d, right :%d\n", maxValue,  left, right);
    if (root->alive) { 
        maxValue = max(max(maxValue , left + root->val), right+root->val);
        /*
        // 2 things we think:
        1. set maximum_value : If current node is alive => set the maximum value -> max(left + curr_val, right + curr_val)
        2. Propagate what : if current node is alive : 2 
        */
    } else {
                if (left != INVALID && right != INVALID) {
            maxValue = max(maxValue, left + right + root->val);
        }
    }

    if (root->alive) {
        return root->val;
    } else {
        return max(left,right) + root->val;
    }
    
}

int findMaximumPathSumSpecial(NodeSpecial* root) {
    int result = INVALID;
     helperSpecial(root, result);
     return result;
}



int main() {
    // int num1, num2;
    // int sum;
    // cin>>num1>>num2;

    // sum = addNumbers(num1,num2);
    // cout<< "The sum is " << sum;
    
//     /*
//                 5
//             /    \  
//             2       0 
//             /       /  \
//         *25      *14  *15
// */
// Node* root = new Node(5);
// root->left = new Node(2);
// root->right = new Node(0);
// root->left->left = new Node(25);
// root->right->left = new Node(14);
// root->right->right = new Node(15);
// cout << "max path is "<< findMaximumPathSum(root) << endl;

// // Test case 2

// /*
//              5
//            /    \  
//          2       0 
//         /  \     / \
//       *100 50  *4   *15
// */
// Node *root2 = new Node (5);
// root2->left = new Node(2);
// root2->left->left = new Node(100);
// root2->left->right = new Node(50);
// root2->right = new Node(0);
//  root2->right->left =new Node(4);
//  root2->right->right = new Node(15);

// cout << "max path of test case 2 is "<< findMaximumPathSum(root2) << endl;

// Node* root3 = new Node(5);
// root3->left = new Node(2);
// cout << "max path of test case 3 is " << findMaximumPathSum(root3) << endl;

// Node* root4 = new Node(6);
// cout << "max path of test case 4 is " << findMaximumPathSum(root4) << endl;
/*
            5
           /    \  
         2*       0 
        /  \     / \
      100*  50* 4*  15*
      */

// NodeSpecial* root = new NodeSpecial(5, false);
// root->left = new NodeSpecial(2, true);
// root->right = new NodeSpecial(0, false);
// root->left->left = new NodeSpecial (100, false);
// root->left->right = new NodeSpecial (50, false);
// root->right->left = new NodeSpecial(4, false);
// root->right->right = new NodeSpecial(15, false);
// cout << "max path is "<< findMaximumPathSumSpecial(root) << endl;
// cout << "max path is "<< findMaximumPathSumSpecial(root) << endl;
// 
/*
      
      
              5
           /    \  
         *40       0 
        /  \     / \
      100*  50* 20*  200*
*/
  NodeSpecial* root = new NodeSpecial(5, false);
root->left = new NodeSpecial(40, true);
root->right = new NodeSpecial(0, false);
root->left->left = new NodeSpecial (100, false);
root->left->right = new NodeSpecial (50, false);
root->right->left = new NodeSpecial(20, false);
root->right->right = new NodeSpecial(200, false);
cout << "max path is "<< findMaximumPathSumSpecial(root) << endl;
    return 0;
}