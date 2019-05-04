#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

/**
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:

The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
*/


class NumArray {

struct TreeNode
{
public:
	TreeNode(int aVal)
	:val(aVal), left(nullptr), right(nullptr) {

	}
	TreeNode(TreeNode* aLeft, TreeNode* aRight)
	: left(aLeft), right(aRight) {
		val = (left ? left->val : 0) + (right ? right->val : 0);
	}
	TreeNode* left;
	TreeNode* right;
	int val;
};
public:
    NumArray(vector<int>& nums)
    :len(nums.size()) {
    	if (!nums.empty())
        	root = buildTree(nums, 0 , nums.size() -1);
    }
    TreeNode* buildTree(vector<int>& nums, int start, int end)
    {
    	if (start == end)
    		return new TreeNode(nums[start]);
    	else
    	{
    		int mid = (start + end) / 2;
    		auto left = buildTree(nums, start, mid);
    		auto right = buildTree(nums, mid + 1, end);
    		auto node = new TreeNode(left, right);
    		return node;
    	}
    }
    

    void update(int i, int val) {

	std::function<int(TreeNode*, int,int, int , int )> updateHelper;
       updateHelper = [&updateHelper](TreeNode* curr, int currStart, int currEnd, int targetIndex, int newVal) -> int
        {
        	if (targetIndex > currEnd || targetIndex < currStart)
        		return curr->val;
        	else if (currStart == currEnd) 
        	{
        		if (currStart == targetIndex)
        		{
        			curr->val = newVal;
        		}
        		  // printf("%d\n",curr->val);
				return curr->val;        			
        	}
        	else
        	{
        		int mid = (currStart + currEnd) / 2;
        		auto left = updateHelper(curr->left, currStart, mid, targetIndex, newVal);
    			auto right = updateHelper(curr->right, mid + 1,  currEnd, targetIndex, newVal);
    			// printf("%d,%d\n", left, right);
    			curr->val = left + right;
    			return curr->val;
        	}
        };
        updateHelper(root, 0, len -1, i, val);
    }
    
    int sumRangeHelper(TreeNode* curr, 
    				int currStart, int currEnd, const int& targetStart, const int& targetEnd)
    {
    	// currStart can never be > currEnd and same for targetStart and targetEnd

    	if (targetStart > currEnd || targetEnd < currStart) // Searching beyond our current valid range
    		return 0;
    	// printf("%d,%d,%d,%d\n", currStart, currEnd, targetStart, targetEnd);
    	assert(curr); // Should never happen
    	// Entire interval contained within current range
    	if (currStart >= targetStart && currEnd <= targetEnd)
    	{
    		return curr->val;
    	}
    	else
    	{
    		int mid = (currStart + currEnd ) / 2;
    		return sumRangeHelper(curr->left, currStart, mid, targetStart, targetEnd)
    			+  sumRangeHelper(curr->right, mid + 1, currEnd, targetStart, targetEnd) ;
    	}
    }
    int sumRange(int i, int j) {
        return sumRangeHelper(root, 0, len - 1, i, j);
    }
    void traverse() {
    	if (!root)
    		return;

    	queue<TreeNode*> nodesRemaining;
    	nodesRemaining.push(root);
    	while (!nodesRemaining.empty()) {
    		int remainingSize = nodesRemaining.size();
    		for (int i = 0; i < remainingSize; i++)
    		{
    			auto node = nodesRemaining.front();
    			nodesRemaining.pop();
    			if (node->left)
    				nodesRemaining.push(node->left);
    			if (node->right)
    				nodesRemaining.push(node->right);
    			cout << node->val << ",";
    		}
    		cout << endl;
    	}
    }

    int len;
	TreeNode* root;
};

int main()
{
	vector<int> v = {1,3,5};
	NumArray numArray(v);
	assert(numArray.sumRange(0, 2) == 9);
	 assert(numArray.sumRange(0,1) == 4);
	 assert(numArray.sumRange(0, 0) == 1);
	assert(numArray.sumRange(2, 2) == 5);
	numArray.update(1, 2);
	assert(numArray.sumRange(0, 2) == 8);
	vector<int> v2;
	NumArray numArray2(v2);
	 // numArray.traverse();
}
