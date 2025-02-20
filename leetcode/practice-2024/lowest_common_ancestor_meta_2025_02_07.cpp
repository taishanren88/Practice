
/*

## Lowest Common Ancestor

Given a tree defined by a set of n nodes:

```
struct Node {
  int id; // Unique for every node
  vector<Node*> children; // The list of direct child nodes
};

Node* root;
```

Plus two nodes: `Node* n1, n2`, find their lowest common ancestor (LCA). Examples:

```
a ┬ b ┬ c
  │   └ w
  ├ x
  └ y ─ z ┬ p
          └ s
```

LCA(a, c) => a; LCA(w, c) => b; LCA(s, w) => a; LCA(p, s) => z;

*/

Node* findLCA(Node* root, Node* a, Node *b ) {
  return nullptr;
  // Search for a. If we find a ,  then we return true
  // Search for b. If we find b, then we return true

  // If result lookin for a is true, then we return a
  // IF result looking for b is true, then we return b
  // If both are true, then we find our LCA, which is just current node 
  auto foundA = helper(root, a, b );
  return foundA;
}

/*
```
a ┬ b ┬ c
  │   └ w
  ├ x
  └ y ─ z ┬ p
          └ s
```
*/

//LCA(a, a, c) => a; LCA(w, c) => b; LCA(s, w) => a; LCA(p, s) => z;

Node* helper (, Node* current, Node* target1, Node* target2 ) {
  if (!current) {
    return nullptr;
  }
  if (current->val == target1->val || current->target2->val) {
          return current;
     } 

     bool found = false;
     Node* result = nullptr;
    for (auto c : current->children) {
     if (helper(c, target1, target2) ) {
       found = true;
       if (found) {
        return current;
       } else {
        result = c;
       }
      }
   }
    return result;
}


