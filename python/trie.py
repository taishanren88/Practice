class TrieNode(object):
      def __init__(self):
        self.end = False
        self.trieSet = {}

class Trie(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = TrieNode()


    def insert(self, word):
        """
        Inserts a word into the trie.
        :type word: str
        :rtype: void
        """
        if self.search(word):
            return

        curr = self.root
        for c in word:
            if c not in curr.trieSet:
                curr.trieSet[c] = TrieNode()
            curr = curr.trieSet[c]

        if curr:
            curr.end = True


    def search(self, word):
        """
        Returns if the word is in the trie.
        :type word: str
        :rtype: bool
        """
        return self.searchImpl(word, False)

    def searchImpl(self, word, startsWith):

        if not word:
            return False

        curr = self.root
        for c in word:
            if c in curr.trieSet:
                curr = curr.trieSet[c]
            else:
                return False

        if startsWith:
            return True
        else:
            return curr and curr.end


    def startsWith(self, prefix):
        """
        Returns if there is any word in the trie that starts with the given prefix.
        :type prefix: str
        :rtype: bool
        """
        return self.searchImpl(prefix, True)

if __name__ == '__main__':
        tree = Trie()
        tree.insert("");
        assert(tree.search("") == False);

        tree.insert("a");
        assert(tree.search("a") == True);

        tree.insert("ab");

        assert(tree.search("ab"));
        assert(tree.search("cd") == False);
        assert(tree.search("c") == False);

        tree.insert("cd");
        assert(tree.search("cd"));

        tree.insert("abe");
        assert(tree.search("a"));
        assert(tree.startsWith("a"));
        assert(tree.startsWith("ab"));
        assert(tree.search("ab"));
        assert(tree.search("abc") == False);

        assert(tree.search("abe"));
        assert(tree.search("c") == False);
        assert(tree.startsWith("c"));
        assert(tree.search("cd"));

        tree2 = Trie();

        tree2.insert("app");
        tree2.insert("apple");
        tree2.insert("beer");
        tree2.insert("add");
        tree2.insert("jam");
        tree2.insert("rental");
        assert(tree2.search("app"));
        assert(tree2.search("apps") == False);
