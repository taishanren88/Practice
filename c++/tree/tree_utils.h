 #include <iostream> 
#include <string>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;
 struct TreeNode {
        int val;
       TreeNode *left;
       TreeNode *right;
       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

    void helper(queue<TreeNode*>& nextLevel, vector<vector<int>>& results)
    {
        const int sizeThisLevel = nextLevel.size();
        vector<int> done; 
        for (int i = 0; i < sizeThisLevel; i++)
        {
            auto node = nextLevel.front();
            nextLevel.pop();
            if (node->left)
                nextLevel.push(node->left);
            if (node->right)
                nextLevel.push(node->right);
            done.push_back(node->val);
        }
        results.push_back(done);
        if (!nextLevel.empty())
            helper(nextLevel, results);
    }
   
  vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if (!root)
            return results;
        
        queue<TreeNode*> level;
        level.push(root);
        helper(level, results);
        return results;
    }

    void levelOrderSerialize(TreeNode* node, string& str)
    {
        if (!node)
            return;
        
        queue<TreeNode*> currentLevel;
        queue<TreeNode*> nextLevel;
        
        currentLevel.push(node);
        while (true)
        {
            while (!currentLevel.empty())
            {
                auto node = currentLevel.front();
                currentLevel.pop();
                if (!node)
                {
                    str += "null,";
                    continue;
                }
                // else cuz I was lazy that's why I wrote it this way
                str += to_string(node->val) + ",";
                if (node->left)
                    nextLevel.push(node->left);
                else
                    nextLevel.push(nullptr);
                if(node->right)
                    nextLevel.push(node->right);
                else
                    nextLevel.push(nullptr);

            }
            if (nextLevel.empty())
                break;
            currentLevel = nextLevel;
            nextLevel = queue<TreeNode*>();
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string serialized;
        levelOrderSerialize(root, serialized);
        return serialized;
    }
      void split(const std::string &s, char delim,vector<TreeNode*>& oElems) 
    {
      std::stringstream ss(s);
      std::string item;
      std::vector<TreeNode*> elems;
      while (std::getline(ss, item, delim)) 
      {
        if (item == "null")
            oElems.push_back(nullptr);
        else
        {
            oElems.push_back(new TreeNode(atoi(item.c_str())));
        }
      }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<TreeNode*> results;
        split(data, ',' , results);
        int nextChild = 1;
        for (int i = 0; i < results.size(); i++)
        {
            auto node = results[i];
            if (node)
            {
                node->left = results[nextChild++];
                node->right = results[nextChild++];
            }
        }
        if (results.empty())
            return nullptr;
        else
            return results[0];
    }
