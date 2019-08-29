/*
 *
 * https://leetcode.com/problems/3sum/
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
 * Note:
 * The solution set must not contain duplicate triplets.
 * Example:
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 * A solution set is:
 * [
 *  [-1, 0, 1],
 *  [-1, -1, 2]
 * ]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int* result(int* nums, int numsSize, int* returnSize);
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

int main()
{
	//int arr[6] = {-1,0,1,2,-1,-4};
	int arr[6] = {0,0,0,0,0,0};
	int * res, res_count, res_column_size = 3;
	res = result(arr, 6, &res_count);
	for (int i = 0; i < res_count; i ++)
	{
		printf("solution %d.\n", i);
		printf("\t[%d", res[i * res_column_size]);
		for (int j = 1; j < res_column_size; j ++)
		{
			printf(",%d", res[i*res_column_size + j]);
		}
		printf("]\n");
	}
	free(res);
	int ** threeSum_res, * returnColumnSizes;
	threeSum_res = threeSum(arr, 6, &res_count, &returnColumnSizes);
	for (int i = 0; i < res_count; i ++)
	{
		printf("website signature solution number %d.\n", i);
		int * res_arr = threeSum_res[i];
		int * cols_width = &(returnColumnSizes[i]);
		printf("\t[%d", res_arr[0]);
		for (int j =1; j < cols_width[0]; j ++)
		{
			printf(",%d", res_arr[j]);
		}
		printf("]\n");
	}
	/* free the arrays from the website signature */
	for (int i = 0; i < res_count; i ++)
	{
		free(threeSum_res[i]);
	}
	free(threeSum_res);
	free(returnColumnSizes);
	return 0;
}

int binary_search(int * arr, int val, int lo, int hi);
int partition(int * arr, int lo, int hi);
void quicksort(int * arr, int lo, int hi);
void swap(int * arr, int a, int b);

int* result(int* nums, int numsSize, int* returnSize)
{
	quicksort(nums, 0, numsSize-1);
	int * res = NULL;
	*returnSize = 0;
	int res_sz = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (i > 0 && nums[i] == nums[i-1]) continue;
		for (int j = i + 1; j < numsSize; j++)
		{
			int remainder_index = binary_search(nums, 0 - nums[i] - nums[j], j+1, numsSize-1);
			if (remainder_index <= j)
			{
				/* cannot have duplicates */
				continue;
			}
			/* solution */
			*returnSize = *returnSize + 1;
			if (res_sz <= (*returnSize) * 3)
			{
				res_sz = res_sz ? res_sz * 2 : 3;
				res = realloc(res, res_sz * sizeof(int));
			}
			res[(*returnSize-1)*3] = nums[i];
			res[(*returnSize-1)*3+1] = nums[j];
			res[(*returnSize-1)*3+2] = nums[remainder_index];
		}
	}
	return res;
}

int binary_search(int * arr, int val, int lo, int hi)
{
	if (lo > hi) return -1;
	int mid_point = (lo+hi)/2;
	if (arr[mid_point] == val) return mid_point;
	if (val < arr[mid_point]) return binary_search(arr, val, lo, mid_point-1);
	return binary_search(arr, val, mid_point+1, hi);
}
int partition(int * arr, int lo, int hi)
{
	int mid_point_val = arr[(lo+hi)/2];
	while (lo <= hi)
	{
		while (arr[lo] < mid_point_val) lo++;
		while (arr[hi] > mid_point_val) hi--;
		if (lo<=hi)
		{
			swap(arr, lo, hi);
			lo++;
			hi--;
		}
	}
	return lo;
}

/* quicksort tested on leetcodee*/
void quicksort(int * arr, int lo, int hi)
{
	/* some base cases */
	if (lo >= hi) return;
	if (lo == hi-1)
	{
		if (arr[lo] > arr[hi])
		{
			swap(arr, lo, hi);
		}
		return;
	}
	
	int partition_index = partition(arr, lo, hi);
	quicksort(arr, lo, partition_index-1);
	quicksort(arr, partition_index, hi);
}

void swap(int * arr, int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int check_duplicate_solution(int ** sols, int res_count, int * new_sol, int sol_sz)
{
	for (int i = 0; i < res_count; i ++)
	{
		int duplicate_solution = 1;
		int * curr_sol = sols[i];
		for (int j = 0; j < sol_sz; j++)
		{
			if (curr_sol[j] != new_sol[j])
			{
				duplicate_solution = 0;
				break;
			}
		}
		if (duplicate_solution) return 1;
	}
	return 0;
}

/* the function signature for the website */
/* the code is copied and pasted from the result function */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
	quicksort(nums, 0, numsSize-1);
	int ** res = NULL;
	*returnSize = 0;
	* returnColumnSizes = NULL;
	int res_sz = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (i > 0 && nums[i] == nums[i-1]) continue; /* cannot have duplicated */
		for (int j = i + 1; j < numsSize; j++)
		{
			int remainder_index = binary_search(nums, 0 - nums[i] - nums[j], j+1, numsSize-1);
			if (remainder_index <= j)
			{
				/* cannot have duplicates */
				continue;
			}
			/* solution */
			int * arr = (int*) malloc(3 * sizeof(int));
			arr[0] = nums[i];
			arr[1] = nums[j];
			arr[2] = nums[remainder_index];
			if (check_duplicate_solution(res, *returnSize, arr, 3))
			{
				free(arr);
				continue;
			}
			*returnSize = *returnSize + 1;
			if (res_sz <= (*returnSize) * 3)
			{
				res_sz = res_sz ? res_sz * 2 : 3;
				res = realloc(res, res_sz * sizeof(int*));
				int returnColumnSizes_alloc = res_sz/3 * sizeof(int*);
				*returnColumnSizes = realloc((*returnColumnSizes), returnColumnSizes_alloc);
			}
			res[(*returnSize)-1] = arr;
			(*returnColumnSizes)[(*returnSize)-1] = 3;
		}
	}
	return res;
}
