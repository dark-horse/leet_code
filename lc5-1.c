/*
 *
 * https://leetcode.com/problems/merge-intervals/
 * Given a collection of intervals, merge all overlapping intervals.
 * Example 1:
 * Input: [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
 * Example 2:
 * Input: [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void swap(int** intervals, int a, int b)
{
	int * tmp = intervals[a];
	intervals[a] = intervals[b];
	intervals[b] = tmp;
}

int partition(int ** intervals, int lo, int hi)
{
	int mid_point = (lo + hi) / 2;
	int * mid_point_interval = intervals[mid_point];
	while (lo <= hi)
	{
		while ( intervals[lo][0] < mid_point_interval[0] ) lo++;
		while ( intervals[hi][0] > mid_point_interval[0] ) hi--;
		if (lo <= hi)
		{
			swap(intervals, lo, hi);
			lo++;
			hi--;
		}
	}
	return lo;
}

void quicksort_intervals(int ** intervals, int lo, int hi)
{
	/* some base cases */
	if (lo >= hi) return;
	if (lo == hi-1)
	{
		if (intervals[lo][0] > intervals[hi][0])
		{
			swap(intervals, lo, hi);
		}
		return;
	}

	int partition_index = partition(intervals, lo, hi);
	quicksort_intervals(intervals, lo, partition_index-1);
	quicksort_intervals(intervals, partition_index, hi);
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes)
{
	quicksort_intervals(intervals, 0, intervalsSize-1);
	int ** res = NULL; int res_capacity = 0; int * res_columnSizes = NULL;
	*returnSize = 0;
	if (!intervals || !intervalsSize)
	{
		*returnColumnSizes = NULL;
		return NULL;
	}

	int * last_interval = (int*) malloc(2 * sizeof(int));
	memcpy(last_interval /*dest*/, intervals[0] /*src*/, 2 * sizeof(int));
	res_capacity = 8;
	res = (int**) malloc(res_capacity * sizeof(int *));
	res[0] = last_interval;
	res_columnSizes = (int*) malloc(res_capacity * sizeof(int));
	res_columnSizes[0] = 2;
	*returnSize = 1;
	for (int i = 1; i < intervalsSize; i ++)
	{
		int * curr_int = intervals[i];
		if(curr_int[0] > last_interval[1])
		{
			/* new interval to add */
			*returnSize = *returnSize + 1;
			if (*returnSize >= res_capacity)
			{
				res_capacity = res_capacity +100;
				res = realloc(res, res_capacity * sizeof(int));
				res_columnSizes = realloc(res_columnSizes, res_capacity * sizeof(int));
			}
			int * new_interval = (int*) malloc(2 * sizeof(int));
			memcpy(new_interval /*dest*/, curr_int /*src*/, 2 * sizeof(int));
			res[(*returnSize)-1] = new_interval;
			res_columnSizes[(*returnSize)-1] = 2;
			last_interval = new_interval;
			continue;
		}
		if (curr_int[1] > last_interval[1])
		{
			last_interval[1] = curr_int[1];
		}
	}
	*returnColumnSizes = res_columnSizes;
	return res;
}

void print_intervals(int ** intervals, int interval_count)
{
	if (!intervals || !interval_count) return;

	printf("[%d,%d] ",intervals[0][0], intervals[0][1]);
	for (int i = 1; i < interval_count; i ++)
	{
		int * interval = intervals[i];
		printf(", [%d,%d] ", interval[0], interval[1]);
	}
	printf("\n");
}

int ** read_input(char * input, int * input_sz)
{
	int ** res, res_capacity = 8;
	*input_sz = 0;
	res = (int **) malloc(res_capacity * sizeof(int*));
	char * pch = strtok(input, "[],");
	while (pch != NULL)
	{
		int left = atoi(pch);
		pch = strtok(NULL, "[],");
		int right = atoi(pch);
		pch = strtok(NULL,"[],");

		int * new_int = (int*) malloc(2 * sizeof(int));
		new_int[0] = left;
		new_int[1] = right;
		*input_sz = *input_sz + 1;
		if (*input_sz >= res_capacity)
		{
			res_capacity = res_capacity * 2;
			res = realloc(res, res_capacity * sizeof(int*));
		}
		res[(*input_sz)-1] = new_int;
	}
	return res;
}

int main()
{
	int int_1[] = {1,3}, int_2[] = {2,6}, int_3[] = {8,10}, int_4[] = {15,18};
	int *input[] = {int_1, int_2, int_3, int_4};
	int output_size, * columnSizes;
	int ** output = merge(input, 4, NULL, &output_size, &columnSizes);
	printf("output size %d.\n", output_size);
	print_intervals(output, output_size);

	int int2_1[] = {1,4}, int2_2[] = {4,5};
	int * input2[] = {int2_1, int2_2};
	output = merge(input2, 2, NULL, &output_size, &columnSizes);
	printf("output size %d.\n", output_size);
	print_intervals(output, output_size);
	int large_input_sz;
	char large_input_string[] = "[[362,367],[314,315],[133,138],[434,443],[202,203],[144,145],[229,235],[205,212],[314,323],[128,129],[413,414],[342,345],[43,49],[333,342],[173,178],[386,391],[131,133],[157,163],[187,190],[186,186],[17,19],[63,69],[70,79],[386,391],[98,102],[236,239],[195,195],[338,338],[169,170],[151,153],[409,416],[377,377],[90,96],[156,165],[182,186],[371,372],[228,233],[297,306],[56,61],[184,190],[401,403],[221,228],[203,212],[39,43],[83,84],[66,68],[80,83],[32,32],[182,182],[300,306],[235,238],[267,272],[458,464],[114,120],[452,452],[372,375],[275,280],[302,302],[5,9],[54,62],[237,237],[432,439],[415,421],[340,347],[356,358],[165,168],[15,17],[259,265],[201,204],[192,197],[376,383],[210,211],[362,367],[481,488],[59,64],[307,315],[155,164],[465,467],[55,60],[20,24],[297,304],[207,210],[322,328],[139,142],[192,195],[28,36],[100,108],[71,76],[103,105],[34,38],[439,441],[162,168],[433,433],[368,369],[137,137],[105,112],[278,280],[452,452],[131,132],[475,480],[126,129],[95,104],[93,99],[394,403],[70,78]]";
	int ** large_input = read_input(large_input_string, &large_input_sz);
	printf("large input has %d intervals,\n", large_input_sz);
	print_intervals(large_input, large_input_sz);
	output = merge(large_input, large_input_sz, NULL, &output_size, &columnSizes);
	printf("number of merged intervals %d.\n", output_size);
	print_intervals(output, output_size);
	return 0;
}

