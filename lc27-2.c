/*
 * https://leetcode.com/problems/russian-doll-envelopes/
 * You have a number of envelopes with widths and heights given as a pair of integers (w, h).
 * One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.
 * What is the maximum number of envelopes can you Russian doll? (put one inside other)
 * Note: Rotation is not allowed.
 * Example: Input: [[5,4],[6,4],[6,7],[2,3]] Output: 3 
 * Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void swap(int ** envelopes, int a, int b)
{
	int * tmp = envelopes[a];
	envelopes[a] = envelopes[b];
	envelopes[b] = tmp;
}

/* sort the envelopes by width */
int partition(int ** envelopes, int lo, int hi)
{
	int pivot_width = envelopes[(lo+hi)/2][0];
	while (lo <= hi)
	{
		while (envelopes[lo][0] < pivot_width) lo++;
		while (envelopes[hi][0] > pivot_width) hi--;
		if (lo <= hi)
		{
			swap(envelopes, lo, hi);
			lo++;
			hi--;
		}
	}
	return lo;
}

void quicksort(int ** envelopes, int lo, int hi)
{
	/* some base cases */
	if (lo >= hi) return;
	if (lo == hi-1)
	{
		if (envelopes[lo][0] > envelopes[hi][0])
		{
			swap(envelopes, lo, hi);
		}
		return;
	}
	int pivot = partition(envelopes, lo, hi);
	quicksort(envelopes, lo, pivot-1);
	quicksort(envelopes, pivot, hi);
}

int max_envelopes_dp_sorted(int ** envelopes, int envelopes_num, int * helper)
{
	helper[envelopes_num-1] = 0;
	int res = 0;
	for (int i = envelopes_num - 2; i >=0; i--)
	{
		int candidate = 0;
		int w_i = envelopes[i][0];
		int h_i = envelopes[i][1];
		for (int j = i+1; j < envelopes_num; j++)
		{
			if (envelopes[j][0] > w_i && envelopes[j][1] > h_i)
			{
				int new_candidate = helper[j] + 1;
				candidate = candidate < new_candidate ? new_candidate : candidate;
			}
		}
		helper[i] = candidate;
		res = res < candidate ? candidate : res;
	}
	return res;
}

int max_envelopes_dp_sorted_recursive(int ** envelopes, int envelopes_num, int * helper, int start)
{
	if (helper[start] != -1) return helper[start];

	int res = 0;
	int w_start = envelopes[start][0];
	int h_start = envelopes[start][1];
	for (int i = start + 1; i < envelopes_num; i ++)
	{
		int candidate = 0;
		if (envelopes[i][0] > w_start && envelopes[i][1] > h_start)
		{
			candidate = max_envelopes_dp_sorted_recursive(envelopes, envelopes_num, helper, i) + 1;
			res = res < candidate ? candidate : res;
		}
	}
	helper[start] = res;
	return res;
}

int max_envelopes_dp(int ** envelopes, int envelopes_num, int * helper, int start)
{
	if (helper[start] != -1) return helper[start];

	int res = 0;
	int w_start = envelopes[start][0];
	int h_start = envelopes[start][1];
	for (int i = 0; i < envelopes_num; i ++)
	{
		if (i == start) continue;
		int candidate = 0;
		if (envelopes[i][0] > w_start && envelopes[i][1] > h_start)
		{
			candidate = max_envelopes_dp(envelopes, envelopes_num, helper, i) + 1;
			res = res < candidate ? candidate : res;
		}
	}
	helper[start] = res;
	return res;
}

int max_envelopes_sorted(int** envelopes, int envelopesSize, int* envelopesColSize)
{
	int * helper = (int *) malloc(sizeof(int) * envelopesSize);
	for (int i = 0; i < envelopesSize; i ++) helper[i] = -1;
	quicksort(envelopes, 0, envelopesSize - 1);
	int res = max_envelopes_dp_sorted(envelopes, envelopesSize, helper);
	free(helper);
	return res + 1;
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize)
{
	if (!envelopes || !envelopesSize) return 0;
	if (envelopesSize > 10) return max_envelopes_sorted(envelopes, envelopesSize, NULL);
	int * helper = (int *) malloc(sizeof(int) * envelopesSize);
	for (int i = 0; i < envelopesSize; i ++) helper[i] = -1;
	for (int i = 0; i < envelopesSize; i ++) max_envelopes_dp(envelopes, envelopesSize, helper, i);
	int res = 0;
	for (int i = 0; i < envelopesSize; i ++) res = res < helper[i] ? helper[i] : res;
	free(helper);
	return res + 1;
}



int main()
{
	int ** envelopes = (int**) malloc(sizeof(int*)*17);
	int e1[] = {6,10};
	int e2[] = {2,4};
	int e3[] = {3,4};
	int e4[] = {3,5};
	int e5[] = {6,7};
	int e6[] = {12,15};
	int e7[] = {4,5};
	int e8[] = {70,24};
	int e9[] = {124,354};
	int e10[] = {5,6};
	int e11[] = {45,2};
	int e12[] = {32,67};
	int e13[] = {31,56};
	int e14[] = {27,45};
	int e15[] = {53,89};
	int e16[] = {52,90};
	int e17[] = {63,101};
	envelopes[0] = e1;envelopes[1] = e2;envelopes[2] = e3;envelopes[3] = e4;envelopes[4] = e5;envelopes[5] = e6;envelopes[6] = e7;envelopes[7] = e8;envelopes[8] = e9;
	envelopes[9] = e10;envelopes[10] = e11;envelopes[11] = e12;envelopes[12] = e13;envelopes[13] = e14;envelopes[14] = e15;envelopes[15] = e16;envelopes[16] = e17;
	printf("max russian dolls %d.\n", maxEnvelopes(envelopes, 17, NULL));

	return 0;
}

