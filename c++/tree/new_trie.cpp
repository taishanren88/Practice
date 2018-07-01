#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct TrieNode
{
    TrieNode()
    {
        for (int i = 0; i < 26; i++)
            values[i] = nullptr;
        end = false;
    }
    shared_ptr<TrieNode> values[26];
    bool end;
};

int getIndex(char c)
{
    return c - 'a';
}

// Think of at trie as a an array of nodes, representing subsequent characters
// Root node represents empty string, its 'values' hold the path
// Unlike a treee node, a trie node holds a PATH, not a value
// *ALWAYS* have a root node
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = make_shared<TrieNode>();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        // For each ch
        auto node = root;
        for (int i = 0; i < word.length(); i++)
        {
            auto charIndex = getIndex(word[i]);
            if (node->values[charIndex] == nullptr)
            {
                node->values[charIndex] = make_shared<TrieNode>();
                node = node->values[charIndex];
            }
            else
                node = node->values[charIndex];
        }
        node->end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto node = root;
        for (int i = 0; i < word.length(); i++)
        {
            auto charIndex = getIndex(word[i]);
            if (node->values[charIndex] == nullptr)
                return false;
            else
                node = node->values[charIndex];
        }
        // Here we reached end of the word
        // So if this word is in the tree, "end" flag should be set to true
        // node guaranteed not to be null at this point
        return node->end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto node = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            auto charIndex = getIndex(prefix[i]);
            if (node->values[charIndex] == nullptr)
                return false;
            else
                node = node->values[charIndex];
        }
        return true;
    }
private:
    shared_ptr<TrieNode> root;
};

int main()
{ 
   Trie obj;
    assert(!obj.search("jimmy"));
    assert(!obj.search("abc"));
    assert(!obj.startsWith("ab"));

    obj.insert("abc");
    assert(obj.search("abc"));
    assert(!obj.search("abcd"));
    assert(obj.startsWith("ab"));

}
