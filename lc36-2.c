/*
 * https://leetcode.com/problems/count-of-range-sum/
 * Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
 * Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.
 * Note: A naive algorithm of O(n2) is trivial. You MUST do better than that.
 * Example: Input: nums = [-2,5,-1], lower = -2, upper = 2, Output: 3 
 * Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct val_index_t
{
	long long val;
	int	index;
} val_index;

void swap(val_index * arr, int a, int b)
{
	val_index tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

long long cmp_val_index(val_index a, val_index b)
{
	return a.val - b.val;
}

int partition_index(val_index * arr, int lo, int hi)
{
	val_index mid_value = arr[(lo+hi)/2];
	while (lo <= hi)
	{
		while (cmp_val_index(arr[lo], mid_value) < (long long) 0) lo++;
		while (cmp_val_index(mid_value, arr[hi]) < (long long) 0) hi--;
		if (lo <= hi)
		{
			swap (arr, lo, hi);
			lo++;
			hi--;
		}
	}
	return lo;
}

void quicksort(val_index * arr, int lo, int hi)
{
	if (lo >= hi) return;
	if (lo == hi-1)
	{
		if (cmp_val_index(arr[lo], arr[hi]) > (long long) 0) swap(arr, lo, hi);
		return;
	}
	int index = partition_index(arr, lo, hi);
	quicksort(arr, lo, index - 1);
	quicksort(arr, index, hi);
}

/* returns the lowest INDEX where arr[INDEX] >= target */
/* if no such index exists (if all items in sorted array < target), returns -1 */
int binary_search_greater_or_equal(val_index * arr, int lo, int hi, long long target)
{
	if (lo > hi) return -1;
	if (arr[hi].val < target) return -1;	/* all items in the array are smaller than target */
	if (arr[lo].val >= target) return lo;	/* all items in the array are greater or equal to the target */

	int mid_point = (lo+hi)/2;
	long long mid_value = arr[mid_point].val;
	if (mid_value == target)
	{
		int res = mid_point;
		while (res > lo && arr[res-1].val >= target) res--;
		return res;
	}
	if (mid_value > target)
	{
		if (mid_point > lo && arr[mid_point-1].val < target) return mid_point;
		return binary_search_greater_or_equal(arr, lo, mid_point-1, target);
	}
	if (mid_point < hi && arr[mid_point+1].val > target) return mid_point + 1;
	return binary_search_greater_or_equal(arr, mid_point + 1, hi, target);
}

/* returns the greatest INDEX where arr[INDEX] <= target */
/* if no such index exists (if all items in sorted array > target), returns -1 */
int binary_search_smaller_or_equal(val_index * arr, int lo, int hi, long long target)
{
	if (lo > hi) return -1;
	if (arr[lo].val > target) return -1;	/* all items in the sorted array are greater than target */
	if (arr[hi].val <= target) return hi;	/* all items in the sorted array are less than or equal to the target */
	int mid_point = (lo+hi)/2;
	long long mid_value = arr[mid_point].val;
	if (mid_value == target)
	{
		int res = mid_point;
		while (res < hi && arr[res+1].val <= target) res++;
		return res;
	}
	if (mid_value < target)
	{
		if (mid_point < hi && arr[mid_point+1].val > target) return mid_point;
		return binary_search_smaller_or_equal(arr, mid_point + 1, hi, target);
	}
	if (mid_point > lo && arr[mid_point-1].val < target) return mid_point - 1;
	return binary_search_smaller_or_equal(arr, lo, mid_point - 1, target);
	
}

int countRangeSum(int* nums, int numsSize, int lower, int upper)
{
	if (!nums || !numsSize) return 0;
	if (numsSize == 1) return (  nums[0] == lower  || nums[0] == lower ) ? 1 : 0;
	val_index * cumm_sum_arr = (val_index *) malloc(sizeof(val_index) * (numsSize));
	long long cumm_sum = 0;
	for (int i = 0; i < numsSize; i ++)
	{
		cumm_sum += (long long) nums[i];
		cumm_sum_arr[i].val = cumm_sum;
		cumm_sum_arr[i].index = i;
	}
	quicksort(cumm_sum_arr, 0, numsSize-1);
	int res = 0;
	for (int i = 0; i < numsSize; i ++)
	{
		long long cumm_i = cumm_sum_arr[i].val;
		int cumm_i_index = cumm_sum_arr[i].index;
		if (cumm_i <= upper && cumm_i >= lower) res ++;
		long long lower_bound_j = (long long) lower + cumm_i;
		long long upper_bound_j = (long long) upper + cumm_i;
		int lower_j = binary_search_greater_or_equal(cumm_sum_arr, 0, numsSize-1, lower_bound_j);
		if (lower_j == -1) continue;
		int upper_j = binary_search_smaller_or_equal(cumm_sum_arr, 0, numsSize-1, upper_bound_j);
		if (upper_j == -1) continue;
		for (int j = lower_j; j <= upper_j; j++)
		{
			if (cumm_sum_arr[j].index > cumm_i_index) res++;
		}
	}
	free(cumm_sum_arr);
	return res;
}



int main()
{
	int input[] = {-2,2};
	printf("countRangeSum is %d.\n", countRangeSum(input, 2, -1, 2));
	int input2[] = {0,0};
	printf("countRangeSum is %d.\n", countRangeSum(input2, 2, -1, 2));
	int input3[] = {-2,0};
	printf("countRangeSum is %d.\n", countRangeSum(input3, 2, -1, 2));
	int input4[] = {-2,5,-1};
	printf("countRangeSum is %d.\n", countRangeSum(input4, 3, -2, -1));
	printf("countRangeSum is %d.\n", countRangeSum(input4, 3, -2, 4));
	int input5[] = {2147483647,-2147483648,-1,0};
	printf("countRangeSum is %d.\n", countRangeSum(input5, 4, -1, 0));
	int input6[] = {-3,1,2,-2,2,-1};
	printf("countRangeSum is %d.\n", countRangeSum(input6, 6, -3, -1));
	return 0;
}

