/*
 *
 * https://leetcode.com/problems/jump-game/
 * Given an array of non-negative integers, you are initially positioned at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Determine if you are able to reach the last index.
 * Example 1: Input: [2,3,1,1,4] Output: true Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 * Example 2: Input: [3,2,1,0,4] Output: false Explanation: You will always arrive at index 3 no matter what. Its maximum
 *             jump length is 0, which makes it impossible to reach the last index.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool canJump_inner(int* nums, int numsSize, bool final)
{
	/* base case */
	if (nums[0] == 0)
    {
        if (numsSize == 1) return true;
        return false;
    }
	for (int i = numsSize-1; i>=0;i--)
	{
		if (nums[i]) continue;
		for (int j = i - 1; j >=0; j--)
		{
			if (nums[j] + j > i || (i == numsSize-1 && nums[j] + j >= i && final)) return canJump_inner(nums, j, false);
		}
		return false;
	}
	return true;
}

bool canJump(int * nums, int numsSize)
{
	return canJump_inner(nums, numsSize, true);
}

int main()
{
	int a[] = {1,0,1,0};
	printf("%s.\n", canJump(a, 4) ? "TRUE" : "FALSE");
	return 0;
}
