#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
# Enter your code here. Read input from STDIN. Print output to STDOUT
"""

          a(1)                                                
        /    \                                                          

      b(2)     c(3)                                               

    /     \        \                                                         

   d(4)   e(4)       f(6)                                               

     New tree 

a_top:  children[b,c]
a_bottom: children[c]
     a(1)

         \

           c(3)

               \

                  f(66)
                  
                       a(1)
                       
1. map of level -> all of the nodes (tree_a)
// [0-> Node(a), 1 -> [Node(b), Node(c)], 2 -> [Noded, Node(e), Node(g)] ]

old_children: d(4), e(5), g(7)
new_children: d(4), e(5), f(6), g(7)
2. For each node in second tree, we check if a node exists. If a ndoe changes its value , that counts as  1
3. If node is deleted , then we just add 1
4. if node is added , then we just add 1 
"""


If a node changes its value, that counts as 1  --> iterate both trees at the same time to check if value changs . I
If a node is deleted then we have to remove everything below it , and then it's the size of the new tree. 
 
 1. If node deleted -> one tree is null. Get size of the other tree
 2. If node is different key -> get size of both trees 
 3. If value changes just do 1 + recurse
 
 
 1. For every node , get a set of the other tree's children and pass that into every child node . For a child node, if the key is hte same (get the children from the other tree , and pass that down.  Continue to iterate over all children 
 2. Iterate 
 
 
b(2)
 
 
  Existing tree                                                   
      a(1)                                                 
     /   \                                                 
   b(2)   c(3)                                   
  /   \     \                                          
d(4)  e(5)   g(7)                       

   New tree
                a(1)
            /         \   
           b(2)        h(8)  
     /      |      \      \    
    d(4)   e(5)   f(6)     g(7) 

 
*/

struct Node {
        string key;
        int value;
        vector<Node> children;
        
        Node(string newkey, int newvalue)
        {
            key = newkey;
            value = newvalue;
        }
 };
 
 
 
unordered_map<string,Node> getChildren(Node x) {
 unordered_map<string, Node> x_children;
      for (auto child_a :x.children){
         x_children[child_a.key] = child_a;
    }
    return x_children;
    
}

 int compareNTreeHelper(unordered_map<string, Node> a_children, unordered_map<string,Node> b_children,
int& num_different) {
    
    for (auto& kv: b_children) {
        Node node = kv.second;
        if (a_children.find(kv.first) != a_children.end()) { // exists in a
             unordered_map<string, Node> a_children = getChildren(a_children[kv.first]);
            unordered_map<string, Node> b_children = getChildren(node);
             compareNTreeHelper(a_children, b_children, num_different);
             a_children.erase(kv.first);
             b_children.erase(kv.first);
             
             // Compute size of remaining nodes in the map
             // auto x= getSubTreeNodeSize(a_children)
             //auto y = getSubTreeNodeSize(b_children)
             int z = 0;
             // Checking if value is different
             if (a_children[kv.first]->second.value != node->value) {
                z = 0 ;
             }
             // add those two 
            //  numDifferent += x + y + z;
             
        }
    }
    return 0;
}


// Itereate over size of remaining subtrees   
int getSubTreeNodeNode(unordered_map<string, Node>) {
    
}
int compareNTree(Node a, Node b) {
    // Iterate over b_children
    // If we can find a similar node in a_children, then we traverse. 
    // If the value is different add 1 .  Remove the node from the a_children and b_children
    // otherwise if we cant find it, then count the size of the tree in both a_children and b_chidlren 
    // 
    unordered_map<string, Node> a_children;
    unordered_map<string, Node> b_children;

    for (auto child_a :a.children){
         a_children[child_a.key] = child_a;
    }
    for (auto child_b : b.children) {
        b_children[child_b.key] = child_b;
    }
    int count = 0;
    compareNTreeHelper(a_children, b_children, count);

    return count;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}