/*
 * https://leetcode.com/problems/increasing-triplet-subsequence/
 * Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.
 * Formally the function should: Return true if there exists i, j, k such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
 * Note: Your algorithm should run in O(n) time complexity and O(1) space complexity.
 * Example 1: Input: [1,2,3,4,5] Output: true
 * Example 2: Input: [5,4,3,2,1] Output: false
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


bool increasingTriplet(int* nums, int numsSize)
{
	if (numsSize < 3) return false;
	if (numsSize == 3) return nums[0] < nums[1] && nums[1] < nums[2];
	#define SENTINEL_VALUE (INT_MAX)
	int first_res = nums[0], second_res = SENTINEL_VALUE;
	int first_candidate = SENTINEL_VALUE;

	for (int i = 1; i < numsSize; i ++)
	{
		if (nums[i] > second_res) return true;	/* first_res, second_res and nums[i] are an increasing triplet */
		if (nums[i] > first_res) second_res = nums[i];
		if (nums[i] < first_candidate)
		{
			first_candidate = nums[i];
			continue;
		}
		if (nums[i] > first_candidate)
		{
			first_res = first_candidate;
			second_res = nums[i];
			first_candidate = SENTINEL_VALUE;
		}
	}
	return false;
}



int main()
{
	int case1[] = {10,9,5,6,3,4,-1,-2,7};
	int case2[] = {10,9,5,6,3,4,-1,-2,2};
	int case3[] = {10,9,5,6,4,-1,-2,5,6};
	int case4[] = {10,9,5,6,4,-1,-2,5,6};
	int case5[] = {10,9,5,6,3,-1,-2,7};
	int case6[] = {10,9,5,6,3,4,-1,-2,2,1};
	int case7[] = {10,9,5,6,3,4,-1,-2,2,3};
	printf("got %s.\n", increasingTriplet(case1, 9) ? "TRUE" : "FALSE");
	printf("got %s.\n", increasingTriplet(case2, 9) ? "TRUE" : "FALSE");
	printf("got %s.\n", increasingTriplet(case3, 9) ? "TRUE" : "FALSE");
	printf("got %s.\n", increasingTriplet(case4, 9) ? "TRUE" : "FALSE");
	printf("got %s.\n", increasingTriplet(case5, 8) ? "TRUE" : "FALSE");
	printf("got %s.\n", increasingTriplet(case6, 10) ? "TRUE" : "FALSE");
	printf("got %s.\n", increasingTriplet(case7, 10) ? "TRUE" : "FALSE");

	return 0;
}

