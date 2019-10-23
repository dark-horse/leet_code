/*
 * https://leetcode.com/problems/longest-increasing-subsequence/
 * Given an unsorted array of integers, find the length of longest increasing subsequence.
 * Example: Input: [10,9,2,5,3,7,101,18], Output: 4 
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 
 * Note: There may be more than one LIS combination, it is only necessary for you to return the length.
 * Your algorithm should run in O(n2) complexity.
 * Follow up: Could you improve it to O(n log n) time complexity?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/* binary search tree */
/* for the purposes of our problem, we only need to implement insertion */
/* the insertion will be similar for avl tree so insertion is O(ln(N)) */
typedef struct binary_search_tree_t
{
	int val;								/* value of the array */
	int count_of_smaller_values;			/* count of values in the array smaller up to when the node was inserted in the tree */
	int bst_sz;								/* how many nodes, including root, are in this bst */
	int height;								/* the height of the tree, including the root */
	struct binary_search_tree_t * l, *r;	/* l->val < val < r->val */
} bst;

bst * alloc_bst(bst * mem_alloc, int * mem_alloc_top)
{
	bst * res = mem_alloc + (*mem_alloc_top);
	*mem_alloc_top = *mem_alloc_top + 1;
	return res;
}

bst * bst_from_val(bst * mem_alloc, int *mem_alloc_top, int val, int count_of_smaller_values)
{
	bst * res = alloc_bst(mem_alloc, mem_alloc_top);
	res->val = val;
	res->count_of_smaller_values = count_of_smaller_values;
	res->bst_sz = 1;
	res->height = 1;
	return res;
}

bst * tree_contains_val(bst * root, int new_val, int count_of_smaller_values)
{
	if (!root) return NULL;
	if (root->val == new_val)
	{
		root->count_of_smaller_values = count_of_smaller_values;
		return root;
	}
	if (root->val > new_val) return tree_contains_val(root->l, new_val, count_of_smaller_values);
	count_of_smaller_values += 1 /*root*/ + (root->l ? root->l->bst_sz : 0);
	return tree_contains_val(root->r, new_val, count_of_smaller_values);
}

/* precondition: new_val does not exist in the tree and root is not NULL and root is balanced */
bst * insert_into_bst_tree(bst * root, int new_val, int count_of_smaller_values, bst * mem_alloc, int* mem_alloc_top, int * lis)
{
	*lis = (*lis<count_of_smaller_values) ? count_of_smaller_values : *lis;
	if (root->val < new_val)
	{
		count_of_smaller_values += 1 /*root*/ + root->bst_sz;
		if (!root->l)
		{
			/* assert root->r == NULL || root->r->height <= 1 */
			bst * new_node = bst_from_val(mem_alloc, mem_alloc_top, root->val, count_of_smaller_values);
			root->l = new_node;
			root->val = new_val;
			root->count_of_smaller_values = root->bst_sz + 1;
			root->height = 2;
			root->bst_sz ++;
			return root;
		}
		else if (!root->r)
		{
			/* assert root->l == NULL || root->l->height <= 1 */
			bst * new_node = bst_from_val(mem_alloc, mem_alloc_top, new_val, count_of_smaller_values);
			root->r = new_node;
			root->height = 2;
			root->bst_sz ++;
			return root;
		}
		else
		{
			bst * insert = insert_into_bst_tree(root->r, new_val, count_of_smaller_values, mem_alloc, mem_alloc_top, lis);
			if (root->r->height - root->l->height <= 1) return insert;
		}
	}
}

typedef struct num_less_count_t
{
	int num;
	int less_num_count;
} num_less_count;

int lengthOfLIS(int* nums, int numsSize)
{
	/* some base cases */
	if (!nums || !numsSize) return 0;
	if (numsSize == 1) return 1;
	if (numsSize == 2) return nums[0] < nums[1] ? 2 : 1;
	num_less_count * tmp = (num_less_count*) malloc(sizeof(num_less_count)* numsSize);
	tmp[0].num = nums[0];
	tmp[0].less_num_count = 0;
	int res = 0;
	for (int i = 1; i < numsSize; i ++)
	{
		tmp[i].num = nums[i];
		int less_num_count = 0;
		for (int j = i - 1;j >=0; j --)
		{
			less_num_count = (tmp[j].num<nums[i] && tmp[j].less_num_count >= less_num_count) ? tmp[j].less_num_count + 1: less_num_count;
		}
		tmp[i].less_num_count = less_num_count;
		res = less_num_count > res ? less_num_count : res;
	}
	free(tmp);
	return res + 1;
}

bool check_bst(bst * root)
{
	if (!root) return true;
	if (!root->r && !root->l) return true;
	return (root->l && root->l->val < root->val) || (root->r && root->r->val < root->val);
}

int main()
{
	int arr[] = {10,9,2,5,3,7,101,18};
	printf("list is %d.\n", lengthOfLIS(arr, 8));
	return 0;
}

