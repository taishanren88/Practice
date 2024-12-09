#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
	TrieNode()
	:children(26, nullptr) {

	}
	bool endsHere;
	vector<TrieNode* > children;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
    	auto n = root;
    	for (int i = 0 ; i < word.size() ; i ++){
    		if (n->children[word[i] - 'a'] != nullptr) { // exists
    			n = n->children[word[i] - 'a'];
    		} else {
    			n->children[word[i] - 'a'] = new TrieNode();
    			n = n->children[word[i] - 'a'];
    		}
    	}
    	n->endsHere = true;
    }
    
    bool search(string word) {
    	auto n = root;
        for (int i = 0 ; i <word.size(); i++) {
        	n = n->children[word[i] - 'a'];
        	 if (n == nullptr ) {
        		return false;
        	}
        }
        return n->endsHere;
    }
    
    bool startsWith(string prefix) {
    	auto n = root;
    	for (int i = 0 ; i < prefix.size() ; i ++){
        	n = n->children[prefix[i] - 'a'];
        	 if (n == nullptr ) {
        		return false;
        	}
    	}
    	return true;
    }

   private:
   	TrieNode* root;
};


int main () {
	Trie* trie = new Trie();
	trie->insert("apple");
	cout << trie->search("apple") << endl;
	cout << trie->search("app") << endl;
	cout << trie->startsWith("app") << endl;
	trie->insert("app");
	cout << trie->search("app") << endl;


	 // Trie* trie2 = new Trie();
	 //  cout << trie2->search("ab") << endl;
	 // trie2->insert("ab");
	 //  cout << trie2->search("ab");
	 //  cout << trie2->search("ab");
	 //  cout << trie2->startsWith("ab");
	 //  cout << trie2->startsWith("ab");
	// cout << trie->search("app") << endl;
}