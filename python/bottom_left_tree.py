# Definition for a binary tree node.
# Note: You may assume the tree (i.e., the given root node) is not NULL.


class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution(object):

    def findBottomLeftValue(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        currQ = []
        nextQ = [root]
        val = root.val
        while nextQ:
            currQ = nextQ # move items from next level into the current queue to be examined
            nextQ = []
            isFirst = True
            while currQ:
                next = currQ.pop(0)
                if isFirst:
                    val = next.val
                    isFirst = False

                if next.left:
                    nextQ.append(next.left)
                if next.right:
                    nextQ.append(next.right)

        return val


if __name__ == '__main__':
    s = Solution()

    """
      2
     / \
    1   3

    """
    tree1 = TreeNode(2)
    assert(s.findBottomLeftValue(tree1) == 2)

    tree1.left = TreeNode(1)
    tree1.right = TreeNode(3)
    assert(s.findBottomLeftValue(tree1) == 1)

    """
      1
     / \
     2 3
    /  / \
   4.  5. 6
      /
      7
    """

    fourthNode = TreeNode(4)
    fifthNode = TreeNode(5)
    fifthNode.left = TreeNode(7)
    sixthNode = TreeNode(6)
    tree1.left.left = fourthNode
    assert(s.findBottomLeftValue(tree1) == 4)

    tree1.right.left = fifthNode
    assert(s.findBottomLeftValue(tree1) == 7)

    tree1.right.right = sixthNode
    assert(s.findBottomLeftValue(tree1) == 7)



