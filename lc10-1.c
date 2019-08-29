/*
 *
 * https://leetcode.com/problems/product-of-array-except-self/
 * Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
 * Example:
 * Input:  [1,2,3,4]
 * Output: [24,12,8,6]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int* productExceptSelf(int* nums, int numsSize, int* returnSize)
{
	if (!nums || !numsSize || !returnSize) return NULL;
	*returnSize = numsSize;
	int * res = (int *) malloc(numsSize * sizeof(int));
	int * helper1 = (int *) malloc(numsSize * sizeof(int));
	int * helper2 = (int *) malloc(numsSize * sizeof(int));

	helper1[0] = 1; helper2[numsSize-1] = 1;
	for (int i = 1; i < numsSize; i ++)
	{
		helper1[i] = helper1[i-1] * nums[i-1];
		helper2[numsSize-1-i] = helper2[numsSize-i] * nums[numsSize-i];
	}
	for (int i = 0; i < numsSize; i ++)
	{
		res[i] = helper1[i] * helper2[i];
	}
	free(helper1);
	free(helper2);
	*returnSize = numsSize;
	return res;
}

int* productExceptSelf_faster(int* nums, int numsSize, int* returnSize)
{
	if (!nums || !numsSize || !returnSize) return NULL;
	*returnSize = numsSize;
	int * res = (int *) malloc(numsSize * sizeof(int));
	int helper1 = 1, helper2 = 1;

	for (int i = 1; i < numsSize; i ++)
	{
		helper1 = helper1 * nums[i-1];
		helper2 = helper2 * nums[numsSize-1-i];
		res[i] = helper1* helper2;
	}
	*returnSize = numsSize;
	return res;
}


void print_array(int * nums, int numsSize)
{
	if (!nums || !numsSize) return;
	printf("[%d", nums[0]);
	for (int i = 1; i < numsSize; i ++)
	{
		printf(", %d", nums[i]);
	}
	printf("]\n");
}

int main()
{
	int nums[] = {1,0,3,4};
	int * res, resSize;
	res = productExceptSelf(nums, 4, &resSize);
	print_array(res, resSize);
	free(res);
	return 0;
}
