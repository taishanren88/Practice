/*
We want to use quad trees to store an N x N boolean grid. Each cell in the grid can only be true or false. The root node represents the whole grid. For each node, it will be subdivided into four children nodes until the values in the region it represents are all the same.

Each node has another two boolean attributes : isLeaf and val. isLeaf is true if and only if the node is a leaf node. The val attribute for a leaf node contains the value of the region it represents.

Your task is to use a quad tree to represent a given grid. The following example may help you understand the problem better:

Given the 8 x 8 grid below, we want to construct the corresponding quad tree:



It can be divided according to the definition above:



 

The corresponding quad tree should be as following, where each node is represented as a (isLeaf, val) pair.

For the non-leaf nodes, val can be arbitrary, so it is represented as *.


*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

Node* divide(const vector<vector<int>>& grid, int top, int bottom, int left, int right) {
    if (top > bottom) return nullptr;
    if (left > right) return nullptr;

    auto val = grid[top][left];
    auto checkSame=[&]() {
        for (int i = top; i <= bottom; i++){
            for (int j = left; j <= right; j++) {
            if (grid[i][j] != val)
                return false;
            }
        }
        return true;
    };
    Node* node = new Node();
    int vertMid = (top + bottom) / 2;
    int horizontalMid = (left + right) / 2;
    if (!checkSame()){
        node->val = false;
        node->isLeaf = false;
        node->topLeft = divide(grid, top, vertMid, left, horizontalMid);
        node->topRight = divide(grid, top, vertMid, horizontalMid + 1, right);
        node->bottomLeft = divide(grid, vertMid + 1, bottom, left, horizontalMid);
        node->bottomRight = divide(grid, vertMid + 1, bottom, horizontalMid + 1, right);
    }
    else {
        node->val = val;
        node->isLeaf = true;
        node->topLeft = node->topRight = node->bottomLeft = node->bottomRight = nullptr;
    }
    return node;
}
Node* construct(vector<vector<int> >& grid) {
    Node* root = divide(grid, 0, grid.size() - 1, 0, grid[0].size() - 1);
    return root;
}

void traverse(Node* node) {
    if (!node) return;
    queue<Node*> remaining;
    remaining.push(node);
    while (!remaining.empty()){
        auto len = remaining.size();
        for (int i = 0; i < len; i++) {
            auto front = remaining.front();
            remaining.pop();
            printf("Leaf: %d, Val :%d,", front->isLeaf, front->val);
            if (front->topLeft)
                remaining.push(front->topLeft);
            if (front->topRight)
                remaining.push(front->topRight);
            if (front->bottomLeft)
                remaining.push(front->bottomLeft);
            if (front->bottomRight)
                remaining.push(front->bottomRight);
        }
        printf("\n");
    }
    printf("Done\n");
}

int main() {
    printf("STARTING\n");
   vector<vector<int>> grid = 
   { {1,1,1,1,0,0,0,0}, {1,1,1,1,0,0,0,0}, {1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,0,0}, {1,1,1,1,0,0,0,0}, {1,1,1,1,0,0,0,0}, {1,1,1,1,0,0,0,0}};
      auto node = construct(grid);
      traverse(node);

}
