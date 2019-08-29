/*
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 * Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 * You are given a target value to search. If found in the array return its index, otherwise return -1.
 * You may assume no duplicate exists in the array.
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0 Output: 4
 * Example 2: 
 * Input: nums = [4,5,6,7,0,1,2], target = 3 Output: -1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* rotation point is index INDX where arr[INDX] > arr[INDX+1] */
int find_rotation_point(int * arr, int lo, int hi)
{
	/* some base cases */
	if (lo == hi-1) return lo;
	int mid_point = (lo+hi) / 2;
	if (arr[mid_point] > arr[mid_point+1]) return mid_point;
	if (arr[mid_point] < arr[hi]) return find_rotation_point(arr, lo, mid_point);
	return find_rotation_point(arr, mid_point, hi);
}

int binary_search(int * nums, int lo, int hi, int target)
{
	if (lo > hi) return -1;
	int mid_point = (lo+hi) / 2;
	if (nums[mid_point] == target) return mid_point;
	if (nums[mid_point] < target) return binary_search(nums, mid_point+1, hi, target);
	return binary_search(nums, lo, mid_point-1, target);
}

int search(int* nums, int numsSize, int target)
{
	if (!nums || !numsSize) return -1;
	if (numsSize == 1) return nums[0] == target ? 0 : -1;
	if (numsSize == 2) return nums[0] == target ? 0 : (nums[1] == target ? 1 : -1);
	if (nums[0] < nums[numsSize-1]) return binary_search(nums, 0, numsSize-1, target);	/* there is no rotation (or rotation is as the end of the array) */
	int rotation_point = find_rotation_point(nums, 0, numsSize-1);

	/* rotation point is the largest integer, rotation_point + 1 is the smallest integer */
	if (target > nums[rotation_point] || target < nums[rotation_point+1]) return -1;

	if (target >= nums[0]) return binary_search(nums, 0, rotation_point, target);
	return binary_search(nums, rotation_point+1, numsSize - 1, target);

}



int main()
{
	int nums[] = {4,5,6,7,0,1,2};
	printf("rotated search for 4 yields %d.\n", search(nums, 7, 4));
	printf("rotated search for 0 yields %d.\n", search(nums, 7, 0));
	printf("rotated search for 3 yields %d.\n", search(nums, 7, 3));
	printf("rotated search for 2 yields %d.\n", search(nums, 7, 2));
	printf("rotated search for 5 yields %d.\n", search(nums, 7, 5));
	int test[] = {5,1,3};
	printf("rotated search for 0 yields %d.\n", search(test, 3, 0));
	int test2[] = {7,8,1,2,3,4,5,6};
	printf("rotated search for 2 yields %d.\n", search(test2, 8, 2));
	return 0;
}
