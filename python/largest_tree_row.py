# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution(object):
    def largestValues(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if not root:
            return []

        currQ = []
        nextQ = [root]
        maxList = []
        while nextQ:
            currQ = nextQ # move items from next level into the current queue to be examined
            nextQ = []
            maximum = None
            while currQ:
                next = currQ.pop(0)
                if maximum is None:
                    maximum = next.val
                elif next.val > maximum:
                    maximum = next.val

                # continue searching on the next level
                if next.left:
                    nextQ.append(next.left)
                if next.right:
                    nextQ.append(next.right)

            maxList.append(maximum)

        return maxList

if __name__ == '__main__':
    s = Solution()

    """
      2
     / \
    1   3
    """
    tree1 = TreeNode(2)
    assert(s.largestValues(tree1) == [2])

    tree1.left = TreeNode(1)
    tree1.right = TreeNode(3)
    assert(s.largestValues(tree1) == [2, 3])

    """
      2
     / \
     1 3
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
    tree1.right.left = fifthNode
    tree1.right.right = sixthNode

    assert(s.largestValues(tree1) == [2, 3, 6, 7])

    tree1 = TreeNode(-40)
    tree1.left = TreeNode(0)
    tree1.right = TreeNode(-37)
    assert(s.largestValues(tree1) == [-40,0 ])
