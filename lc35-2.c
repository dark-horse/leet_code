/*
 * https://leetcode.com/problems/count-of-smaller-numbers-after-self/
 * You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].
 * Example:  Input: [5,2,6,1]  Output: [2,1,1,0] 
 * Explanation:
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define max(a,b) ( (a<b) ? b : a)

typedef struct avl_tree_t
{
	long long val;
	int size;			/* how many nodes are in this tree? includes the root */
	int counts;			/* how many times this node was added to the tree */
	int height;			/* includes the root */
	struct avl_tree_t * l, *r;
} avl_tree;

avl_tree * node_from_val(long long val)
{
	avl_tree * res = (avl_tree*) malloc(sizeof(avl_tree));
	res->val = val;
	res->height = 1;
	res->size = 1;
	res->counts = 1;
	res->l = NULL;
	res->r = NULL;
	return res;
}

void update_tree_height_size(avl_tree * t)
{
	if (!t) return;
	int l_height = 0, r_height = 0, l_size = 0, r_size = 0;
	if (t->l)
	{
		l_height = t->l->height;
		l_size = t->l->size;
	}
	if (t->r)
	{
		r_height = t->r->height;
		r_size = t->r->size;
	}
	t->size = l_size + r_size + t->counts;
	t->height = 1 + max(l_height, r_height);
}

/* PRECONDITION: !root->l | !root->r */
avl_tree * balance_two_level_tree(avl_tree * root)
{
	avl_tree * res, *r = root->r, *l = root->l;
	if (!root->l)
	{
		if (root->r->l)
		{
			/* assert(!root->r->r) */
			res = r->l;
			res->r = r;
			res->r->height = 1;
			res->r->size = res->r->counts;
			res->r->l = NULL;
		}
		else
		{
			res = r;
		}
		res->l = root;
		root->r = NULL;
	}
	else
	{
		/* assert (!root->r) */
		if (root->l->r)
		{
			/* assert(!root->l->l) */
			res = l->r;
			res->l = l;
			res->l->height = 1;
			res->l->size = res->l->counts;
			res->l->r = NULL;
		}
		else
		{
			res = root->l;
		}
		res->r = root;
		root->l = NULL;
	}
	res->height = 2;
	res->size = res->counts + res->l->counts + res->r->counts;
	root->height = 1;
	root->size = root->counts;
	return res;
}


/* PRECONDITION: tree_height(root->l) + 1 < tree_height(root->r) */
avl_tree * rotate_left(avl_tree * root)
{
	avl_tree * l = root->l, * r = root->r, * r_l = root->r->l, * r_r = root->r->r;
	avl_tree * res;
	if (r_r->height == l->height+1)
	{
		res = r;
		root->r = r_l;
	}
	else
	{
		avl_tree * r_l_l = r_l->l, * r_l_r = r_l->r;
		/* assert(r_r->height == l->height && r_l->height == l->height + 1) */
		res = r_l;
		res->l = root;
		res->r = r;
		root->r = r_l_l;
		r->l = r_l_r;
		update_tree_height_size(r);
	}
	res->l = root;
	update_tree_height_size(root);
	update_tree_height_size(res);
	return res;
}

/* PRECONDITION: tree_height(root->r) + 1 < tree_height(root->l) */
avl_tree * rotate_right(avl_tree * root)
{
	avl_tree * l = root->l, * r = root->r, * l_l = root->l->l, * l_r = root->l->r;
	avl_tree * res;
	if (l_l->height == r->height + 1)
	{
		res = l;
		root->l = l_r;
	}
	else
	{
		avl_tree * l_r_l = l_r->l, * l_r_r = l_r->r;
		res = l_r;
		res->l = l;
		res->r = root;
		root->l = l_r_r;
		l->r = l_r_l;
		update_tree_height_size(l);
	}
	res->r = root;
	update_tree_height_size(root);
	update_tree_height_size(res);
	return res;
}

avl_tree * insert_val(avl_tree * root, long long val)
{
	if (!root) return node_from_val(val);
	
	if (val == root->val)
	{
		root->counts ++;
		root->size ++;
		return root;
	}
	if (val < root->val)
	{
		root->l = insert_val(root->l, val);
	}
	else
	{
		root->r = insert_val(root->r, val);
	}
	int l_height = root->l ? root->l->height : 0;;
	int r_height = root->r ? root->r->height : 0;
	update_tree_height_size(root);
	if (l_height - r_height <= 1 && l_height - r_height >= -1) return root;
	if (!root->l || !root->r)
	{
		return balance_two_level_tree(root);
	}
	else if (r_height - l_height > 1)
	{
		return rotate_left(root);
	}
	else
	{
		return rotate_right(root);
	}
}

int count_nodes_less_than_val(avl_tree * root, long long val, int count_so_far)
{
	if (!root) return count_so_far;
	if (root->val > val) return count_nodes_less_than_val(root->l, val, count_so_far);
	int l_size = root->l ? root->l->size : 0;
	int r_size = root->r ? root->r->size : 0;
	int root_nodes_count = root->size - l_size - r_size;
	int res = count_so_far + l_size + root_nodes_count;
	if (root->val < val) res = count_nodes_less_than_val(root->r, val, res);
	return res;
}

void free_tree(avl_tree * root)
{
	if (!root) return;
	free_tree(root->l);
	free_tree(root->r);
	free(root);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int* nums, int numsSize, int* returnSize)
{
	if (!nums || !numsSize)
	{
		*returnSize = 0;
		return NULL;
	}
	int * res = (int *) malloc(numsSize * sizeof(int));
	*returnSize = numsSize;
	avl_tree * root = NULL;
	for (int i = numsSize - 1; i >= 0; i--)
	{
		int count = count_nodes_less_than_val(root, nums[i]-1, 0);
		res[i] = count;
		root = insert_val(root, nums[i]);
	}
	free_tree(root);
	return res;
}


void print_int_arr(int * arr, int arr_sz)
{
	if (!arr || !arr_sz) return;
	printf("[%d", arr[0]);
	for (int i = 1; i < arr_sz; i ++)
	{
		printf(", %d", arr[i]);
	}
	printf("]\n");
}

int main()
{
	int input[] = {5,4,3,2,1};
	int returnSize = 0;
	int * res = countSmaller(input, 5, &returnSize);
	print_int_arr(res, returnSize);
	res = countSmaller(input, 1, &returnSize);
	print_int_arr(res, returnSize);
	int input2[] = {5,4,3,3,3};
	res = countSmaller(input2, 5, &returnSize);
	print_int_arr(res, returnSize);
	return 0;
}

