#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

/* g++ trie.cpp -o trie -std=c++0x */
struct TrieNode
{
    TrieNode()
    {
        for (int i = 0; i < 26 ;i++)
            trieSet[i] = nullptr;
        end = false;
    }
    TrieNode* trieSet [26];
    bool end;

};

/* Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.
*/
class Trie
{
public:

    TrieNode* root;

    Trie()
    {
        root = new TrieNode();
        root->end = false;
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        if (search(word))
            return;

        if (word.size() == 0)
            return;

        TrieNode* curr = root;
        TrieNode* nextNode = nullptr;
        for (char c : word)
        {
            nextNode = curr->trieSet[getIndex(c)]; // get the next child potentially containing the current character
            if (!nextNode) // doesn't exist, so allocate
            {
                curr->trieSet[getIndex(c)] = new TrieNode();
                nextNode = curr->trieSet[getIndex(c)]; // next iteration we work on this also
            }
            curr = nextNode;
        }

        if (curr)
            curr->end = true;
    }

    /** Returns if the word is in the trie. */
    bool search(std::string word) const
    {
        return searchWrapper(word, root, false);
    }

    bool searchWrapper(std::string word, TrieNode* curr, bool prefixSearch) const
    {
       if (word.empty())
            return false;

        for (int i = 0; i < word.size(); i++)
        {
            char c = word[i];
            if (curr && curr->trieSet[getIndex(c)])
                curr = curr->trieSet[getIndex(c)];
            else
                return false;
        }
        return curr && (prefixSearch ? true : curr->end);
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        return searchWrapper(prefix, root, true);
    }

    int getIndex(char c) const
    {
        return (int) (c - 'a');
    }
    void print()
    {
        queue<TrieNode*> level;
        level.push(root);

        TrieNode* curr;
        while (!level.empty())
        {
            curr = level.front();
            level.pop();

            for (int i = 0; i < 26; i++)
            {
                if (curr->trieSet[i])
                {
                    std::cout << (char) (i + 'a') << ':' << (int)curr->trieSet[i]->end <<',';
                    level.push(curr->trieSet[i]);
                }
            }
            std::cout << endl;
        }
    }

};


int main()
{
    Trie tree;
    tree.insert("");
    assert(!tree.search(""));
    tree.insert("a");
    assert(tree.search("a"));

    tree.insert("ab");

    assert(tree.search("ab"));
    tree.insert("cd");
    assert(tree.search("cd"));
    tree.insert("abe");
    tree.print();
    assert(tree.search("a"));
    assert(tree.startsWith("a"));
    assert(tree.startsWith("ab"));
    assert(tree.search("ab"));
    assert(!tree.search("abc"));

    assert(tree.search("abe"));
    assert(!tree.search("c"));
    assert(tree.startsWith("c"));
    assert(tree.search("cd"));


    Trie tree2;
    tree2.insert("app");

    tree2.insert("apple");
    tree2.insert("beer");
    tree2.insert("add");
    tree2.insert("jam");
    tree2.insert("rental");
    assert(tree2.search("app"));
    assert(!tree2.search("apps"));
}
