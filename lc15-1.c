/*
 *
 * https://leetcode.com/problems/sliding-window-maximum/
 * Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.
 * Example: Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
 * Output: [3,3,5,5,6,7] 
 * Explanation: 
 * Window position                Max
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 *  1 [3  -1  -3] 5  3  6  7       3
 *  1  3 [-1  -3  5] 3  6  7       5
 *  1  3  -1 [-3  5  3] 6  7       5
 *  1  3  -1  -3 [5  3  6] 7       6
 *  1  3  -1  -3  5 [3  6  7]      7
 * Note: You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.
 * Follow up: Could you solve it in linear time?
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int * create_heap(int hp_sz) { return (int*) malloc(sizeof(int) * hp_sz); }

void free_heap(int * hp) { free(hp); }

void add_new_element(int * hp, int index, int new_elem)
{
	/* base case: first time we insert into the heap */
	if(index == 0)
	{
		hp[index] = new_elem;
		return;
	}

	int parent_index = (index-1) / 2;

	if (new_elem > hp[parent_index])
	{
		hp[index] = hp[parent_index];
		add_new_element(hp, parent_index, new_elem);
	}
	else
	{
		hp[index] = new_elem;
	}
}

/* pre-condition: hp contains old_elem */
bool swap_element_in_full_heap(int * hp, int hp_sz, int index, int old_elem, int new_elem)
{
	if (old_elem == new_elem) return true;

	if (hp[index] == old_elem)
	{
		hp[index] = new_elem;
		/* do we need to rebalance the heap? */
		/* check parent */
		int current_index = index;
		int parent_index = (current_index >0) ? (current_index - 1) / 2 : -1;
		while (parent_index >= 0 && hp[parent_index] < new_elem)
		{
			hp[current_index] = hp[parent_index];
			hp[parent_index] = new_elem;
			current_index = parent_index;
			parent_index = (current_index > 0) ? (current_index - 1) / 2 : -1;
		}
		/* check children if available */
		if ( (2*index+1>=hp_sz || hp[2*index+1] <= hp[index]) && (2*index+2>=hp_sz || hp[2*index+2] <= hp[index]) ) return true;
		int swap_children_index = (hp[2*index+1] > hp[index]) ? 2*index+1 : 2*index+2;
		if (2*index+2 < hp_sz && hp[2*index+2] > hp[index] && hp[2*index+2] > hp[2*index+1]) swap_children_index = 2 * index + 2;
		hp[index] = hp[swap_children_index];
		swap_element_in_full_heap(hp, hp_sz, swap_children_index, hp[swap_children_index], new_elem);
		return true;
	}
	else
	{
		bool swapped = false;
		if (2*index+1 < hp_sz) swapped = swap_element_in_full_heap(hp, hp_sz, 2*index+1, old_elem, new_elem);
		if (!swapped && 2*index+2 < hp_sz) swapped = swap_element_in_full_heap(hp, hp_sz, 2*index+2, old_elem, new_elem);
		return swapped;
	}
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
	*returnSize = numsSize - k + 1;
	/* some base cases */
	if (!nums || !numsSize) return NULL;
	if (k == 1)
	{
		int * res = (int *) malloc(sizeof(int) * numsSize);
		memcpy(res /*dest*/, nums /*src*/, numsSize * sizeof(int));
		return res;
	}
	if (k == numsSize)
	{
		int * res = (int *) malloc(sizeof(int));
		int max = INT_MIN;
		for (int i = 0; i < numsSize; i++)
		{
			if (nums[i] > max) max = nums[i];
		}
		*res = max;
		return res;
	}
	int * hp = create_heap(k);
	for (int i = 0; i < k; i ++)
	{
		add_new_element(hp, i, nums[i]);
	}
	int * res = (int *) malloc((numsSize-k+1)*sizeof(int));
	*res = hp[0];
	for (int i = k; i < numsSize; i ++)
	{
		int old_elem = nums[i-k];
		int new_elem = nums[i];
		swap_element_in_full_heap(hp, k, 0, old_elem, new_elem);
		res[i-k+1] = hp[0];
	}

	free(hp);
	return res;
}

int find_max(int* nums, int k)
{
    int res = INT_MIN;
    for (int i = 0; i < k; i ++)
    {
        if(nums[i]>res) res = nums[i];
    }
    return res;
}

/* a simple maxSlidingWindow which is faster than 98% of all leetcode and faster than the one that uses a heap */
int* maxSlidingWindow_simple(int* nums, int numsSize, int k, int* returnSize)
{
	*returnSize = numsSize - k + 1;
	/* some base cases */
	if (!nums || !numsSize) return NULL;
	if (k == 1)
	{
		int * res = (int *) malloc(sizeof(int) * numsSize);
		memcpy(res /*dest*/, nums /*src*/, numsSize * sizeof(int));
		return res;
	}
	if (k == numsSize)
	{
		int * res = (int *) malloc(sizeof(int));
		int max = INT_MIN;
		for (int i = 0; i < numsSize; i++)
		{
			if (nums[i] > max) max = nums[i];
		}
		*res = max;
		return res;
	}
	int * res = (int *) malloc((numsSize-k+1)*sizeof(int));
    int max_so_far = find_max(nums, k);
    res[0] = max_so_far;
    for (int i = 1; i < numsSize-k+1; i++)
    {
        max_so_far = nums[i+k-1]>max_so_far ? nums[i+k-1] : max_so_far;
        if (nums[i-1]>=max_so_far) max_so_far = find_max(nums+i, k);
        res[i] = max_so_far;
    }
	return res;
}

void print_array(int *arr, int arr_sz)
{
	if (!arr || !arr_sz) return;
	printf("[%d", arr[0]);
	for (int i = 1; i < arr_sz; i ++)
	{
		printf(",%d", arr[i]);
	}
	printf("]\n");
}

int main()
{

	//int inp[] = {1,3,-1,-3,5,3,6,7};
	int inp[] = {1,3,1,2,0,5};
	int res_sz;
	int * res = maxSlidingWindow(inp, 6, 3, &res_sz);
	print_array(res, res_sz);
	free(res);

	return 0;
}
