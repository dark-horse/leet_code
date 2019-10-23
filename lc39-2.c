/*
 * https://leetcode.com/problems/max-chunks-to-make-sorted-ii/
 * Given an array arr of integers (not necessarily distinct), we split the array into some number of "chunks" (partitions), and individually sort each chunk.  After concatenating them, the result equals the sorted array.
 * What is the most number of chunks we could have made?
 * Example 1: Input: arr = [5,4,3,2,1] Output: 1
 * Explanation: Splitting into two or more chunks will not return the required result.
 * For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
 * Example 2: Input: arr = [2,1,3,4,4] Output: 4
 * Explanation: We can split into two chunks, such as [2, 1], [3, 4, 4]. However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.
 * Note: arr will have length in range [1, 2000]. arr[i] will be an integer in range [0, 10**8].
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

int max_chunks_recursive(int * max_arr, int * min_arr, int hi, int arr_sz)
{
	/* some base cases */
	if (hi < 0) return 0;
	if (hi == 0) return 1;

	int index = hi;
	while (index > 0 && max_arr[index-1] > min_arr[index]) index --;
	return max_chunks_recursive(max_arr, min_arr, index-1, arr_sz) + 1;
}

int maxChunksToSorted(int* arr, int arrSize)
{
	/* some base cases */
	if (arrSize <= 1) return arrSize;
	if (arrSize == 2) return arr[0] > arr[1] ? 1 : 2;

	int * max_arr = (int *) malloc(sizeof(int)*arrSize);
	int * min_arr = (int *) malloc(sizeof(int)*arrSize);
	int min_so_far = INT_MAX;
	int max_so_far = INT_MIN;
	for (int i = 0; i < arrSize; i ++)
	{
		if (arr[i] > max_so_far) max_so_far = arr[i];
		max_arr[i] = max_so_far;
		if (arr[arrSize - 1 - i] < min_so_far) min_so_far = arr[arrSize - 1 - i];
		min_arr[arrSize - 1 - i] = min_so_far;
	}
	int res = max_chunks_recursive(max_arr, min_arr, arrSize - 1, arrSize);
	free(min_arr);
	free(max_arr);
	return res;
}



int main()
{
	int input[] = {5, 4, 6, 2, 1};
	printf("max chunks are %d.\n", maxChunksToSorted(input, 5));
	return 0;
}

