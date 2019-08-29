/*
 *
 * https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/
 * Given a binary tree, find the length of the longest consecutive sequence path.
 *The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).
 * Example 1: Input:
 *   1
 *    \
 *     3
 *    / \
 *   2   4
 *        \
 *         5
 * Output: 3 Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
 * Example 2: Input:
 *   2
 *    \
 *     3
 *    / 
 *   2    
 *  / 
 * 1
 *Output: 2 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void longest_consecutive_with_parent(int parent_val, struct TreeNode* node, int * longest, int *current_longest)
{
	if (!node) return;
	if (node->val == parent_val + 1)
	{
		*current_longest = *current_longest + 1;
		if (*current_longest > *longest) *longest = *current_longest;
	}
	else
	{
		*current_longest = 1;
	}
	int curr_longest = *current_longest;
	longest_consecutive_with_parent(node->val, node->left, longest, current_longest);
	*current_longest = curr_longest;
	longest_consecutive_with_parent(node->val, node->right, longest, current_longest);
}

int longestConsecutive(struct TreeNode* root)
{
	if (!root) return 0;
	if (!root->left && !root->right) return 1;
	int longest = 1, curr_longest = 1;
	longest_consecutive_with_parent(root->val, root->left, &longest, &curr_longest);
	curr_longest = 1;
	longest_consecutive_with_parent(root->val, root->right, &longest, &curr_longest);
	return longest;
}


int main()
{
	return 0;
}
