/*
 * https://leetcode.com/problems/closest-binary-search-tree-value/
 * Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.
 * Note: Given target value is a floating point. You are guaranteed to have only one unique value in the BST that is closest to the target.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define abs_macro(a) ( (a)>0 ? (a) : 0-(a) )

/* to work around 32 bits limits, because these are the testcases in LEETCODE these days */
int integer_subtraction(int a, int b)
{
	if (a > 0)
	{
		if (b >= 0) return a-b;
		if (INT_MAX + b <= a) return INT_MAX;
		return a-b;
	}
	else if (a == 0)
	{
		if (b == INT_MAX) return INT_MIN;
		if (b == INT_MIN) return INT_MAX;
		return a-b;
	}
	else
	{
		if (b <= 0 ) return a-b;
		if (INT_MIN + b >= a) return INT_MIN;
		return a-b;
	}
}

int closestValue_int_target(struct TreeNode* root, int target)
{
	/* assert(root) */
	if (target == root->val) return root->val;
	int children_closest_value = root->val;
	if (root->left && root->val > target)
	{
		children_closest_value = closestValue_int_target(root->left, target);
	}
	else if (root->right && root->val < target)
	{
		children_closest_value = closestValue_int_target(root->right, target);
	}
	long int root_dist = root->val - target;
	long int child_dist = children_closest_value - target;
	return (abs_macro(root_dist) < abs_macro(child_dist)) ? root->val : children_closest_value;
}

int closestValue(struct TreeNode* root, double target)
{
	/* assert(root) */
	return closestValue_int_target(root, round(target));
}

struct TreeNode * node_from_val(int val)
{
	struct TreeNode * res = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	res->val = val;
	res->left = NULL;
	res->right = NULL;
	return res;
}


int main()
{
	struct TreeNode * root = node_from_val(4);
	root->right = node_from_val(5);
	root->left = node_from_val(2);
	root->left->left = node_from_val(1);
	root->left->right = node_from_val(3);
	printf("closest neighbour is %d.\n", closestValue(root, 3.412));
	return 0;
}

