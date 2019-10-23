/*
 * https://leetcode.com/problems/trapping-rain-water/
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
 * Example: Input: [0,1,0,2,1,0,1,3,2,1,2,1] Output: 6
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


int calc_vol(int * heights, int lo, int hi)
{
	int height = heights[lo] > heights[hi] ? heights[hi] : heights[lo];
	int res = 0;
	for (int i = lo + 1; i < hi; i ++)
	{
		if (heights[i] >= height) continue;
		res += height - heights[i];
	}
	return res;
}

void mark_ends(int * heights, int heightsSize)
{
	int max = heights[heightsSize-1];
	for (int i = heightsSize-1; i >= 0; i --)
	{
		if (heights[i] > max)
		{
			max = heights[i];
			heights[i] = 0- heights[i];
		}
	}
}

int trap(int* height, int heightSize)
{
	if (heightSize < 3) return 0;
	mark_ends(height, heightSize);
	int res = 0;

	for (int i = 0; i < heightSize;)
	{
		int start = i;
		if (height[start] < 0) height[start] = 0 - height[start];
		while (start + 1 < heightSize && height[start] <= height[start+1]) start ++;
		int end = start + 1;
		while (true)
		{
			if (end >= heightSize-1) break;
			if (height[end] < 0)
			{
				height[end] = 0 - height[end];
				break;
			}
			if (height[end] >= height[start]) break;
			end ++;
		}
		if (start < heightSize && end < heightSize)
		{
			res += calc_vol(height, start, end);
		}
		i = end;
	}
	return res;
}



int main()
{
	int input[] = {10,1,2,3,2,3,7,6,2,4,3,4,6,8};
	printf("volume is %d.\n", trap(input, 16));
	return 0;
}

