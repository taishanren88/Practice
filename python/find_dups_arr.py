#Given an array of integers, 1 <= a[i] <= n (n = size of array),some elements appear twice and others appear once.
#Find all the elements that appear twice in this array.

#Could you do it without extra space and in O(n) runtime?


class Solution(object):
    def findDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        dups = []
        index = 0
        for integer in nums:
            nextInteger = integer
            while ((nextInteger > 0) and (nextInteger -1 != index)): # While current number is not in its right place
                nextIndex = nextInteger -1

                # update our current index at its right location
                if nums[nextIndex] == -1:
                    nums[nextIndex] = 0 # already existing
                    dups.append(nextInteger)
                    break

                else:
                    nums[index] = nums[nextIndex]
                    nums[nextIndex] = -1 # set to -1
                    nextInteger = nums[index] # Re-examine current

            if  nums[index] -1 == index and nums[index] != -1: # if we haven't movd and in right place
                nums[index] = -1

            index = index + 1

        return dups


if __name__ == '__main__':
    s = Solution()
    emptyDups = [1, 2, 3, 4]
    assert(len(s.findDuplicates(emptyDups)) == 0)
    dups = [1 , 1]
    assert(s.findDuplicates(dups) == [1])

    dups = [1 , 1, 2, 3]
    assert(s.findDuplicates(dups) == [1])

    dups = [4, 2, 3, 1, 3, 2]

    assert(sorted(s.findDuplicates(dups)) == [2, 3])
