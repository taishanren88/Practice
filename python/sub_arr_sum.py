#!/usr/bin/python
import unittest

"""
		Given an array of integers and an integer k,
		you need to find the total number of continuous subarrays whose sum equals to k.
		Short: Search through array , check if there's some sum which is a multiple of k.
"""
class Solution(object):
    def checkSubarraySum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        my_dict = {0: -1}
        # Check if some sum is multiple of k
        # Assume SumI is ith some from 0 to i
        # Assume SumJ is jth sum from 0 to j, j > i
        # There is some subarray SumJ - SumI is multiple of k , or SumJ - SumI  = n * k
        # In other words, SumI + n * k = SumJ. Know SumI also has some RemainderI
        # We know (SumI + n * k ) mod (n * k )=>  RemainderI or (SumJ) mod (n * k) == RemainderJI
        # When Remainder J == Remainder I with a distance of 2, we have found such subarray
        sum = 0;
        i = 0;
        for x in nums:
        	if k == 0:
        		if x == 0 and i < len(nums) -1 and nums[i+1] == 0:
        			return True
        	else:
        		sum += x
        		rem = sum % k;
        		if rem in my_dict:
        			if (i - my_dict[rem] >= 2):
        				return True
        		else:
        			my_dict[rem] =i
        	i+=1
        return False


if __name__ == '__main__':
	xyz = Solution()
	v = [2, 2, 1, 2]
	assert(xyz.checkSubarraySum(v, 3) ==  True)
	assert(xyz.checkSubarraySum(v, 6) ==  False)
	assert(xyz.checkSubarraySum(v, 0) == False)

	v = [23, 2, 4, 6, 7]
	assert(xyz.checkSubarraySum(v, 6) == True)
	assert(xyz.checkSubarraySum(v, 1) == True)

	v = [0 , 0];
	assert(xyz.checkSubarraySum(v, 0) == True)
	v =[ 0, 6, 0];
	assert(xyz.checkSubarraySum(v, 0) == False)

	v= [23, 2, 4];
	assert(xyz.checkSubarraySum(v, 6) == True)
	v = [ 2, 4];
	assert(xyz.checkSubarraySum(v, 6) == True)
	v= [0];
	assert(xyz.checkSubarraySum(v, -1) == False)

