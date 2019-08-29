/*
 *
 * https://leetcode.com/problems/binary-tree-longest-consecutive-sequence-ii/
 * Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.
 * Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.
 * Example 1: Input:
 *        1
 *       / \
 *       2   3
 * Output: 2 Explanation: The longest consecutive path is [1, 2] or [2, 1].
 * Example 2: Input:
 *        2
 *       / \
 *      1   3
 * Output: 3 Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
 * Note: All the values of tree nodes are in the range of [-1e7, 1e7]. 
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

typedef struct queue_t
{
	struct TreeNode ** arr;
	int first, last;
} queue;

void enqueue(queue * q, struct TreeNode * t)
{
	q->arr[q->last] = t;
	q->last ++;
}

struct TreeNode * dequeue(queue * q)
{
	struct TreeNode * res = q->arr[q->first];
	q->first ++;
	return res;
}

void longest_recursive(struct TreeNode* root, int * longest, int *curr_longest_descending_inc, int *curr_longest_descending_not_inc, int increment)
{
	/* some base cases */
	if (!root) return;
	if (!root->left && !root->right)
	{
		*curr_longest_descending_inc = 1;
		*curr_longest_descending_not_inc = 1;
		return;
	}

	int l_desc_inc = 0, l_desc_not_inc = 0, r_desc_inc = 0, r_desc_not_inc = 0;
	longest_recursive(root->left, longest, &l_desc_inc, &l_desc_not_inc, increment);
	longest_recursive(root->right, longest, &r_desc_inc, &r_desc_not_inc, increment);

	/* check the descending longest consecutive sequence in the incremental order*/
	int longest_descending_inc = 0;
	if (root->left && root->left->val == root->val + increment)
	{
		longest_descending_inc = l_desc_inc;
	}
	if (root->right && root->right->val == root->val + increment && r_desc_inc > longest_descending_inc)
	{
		longest_descending_inc = r_desc_inc;
	}
	*curr_longest_descending_inc = longest_descending_inc + 1;
	if (*curr_longest_descending_inc > *longest) *longest = *curr_longest_descending_inc;

	/* same for not in incremental order */
	int longest_descending_not_inc = 0;
	if (root->left && root->left->val == root->val - increment)
	{
		longest_descending_not_inc = l_desc_not_inc;
	}
	if (root->right && root->right->val == root->val - increment && r_desc_not_inc > longest_descending_not_inc)
	{
		longest_descending_not_inc = r_desc_not_inc;
	}
	*curr_longest_descending_not_inc = longest_descending_not_inc + 1;

	/* now snap the child - parent - child sub trees together and see if we get a bigger sequence */
	if (root->left && root->right)
	{
		int child_parent_child = 0;
		if (root->left->val == root->val - increment && root->right->val == root->val + increment)
		{
			child_parent_child = 1 + l_desc_not_inc + r_desc_inc;
		}
		if (root->left->val == root->val + increment && root->right->val == root->val - increment)
		{
			int new_child_parent_child = 1 + l_desc_inc + r_desc_not_inc;
			child_parent_child = (new_child_parent_child > child_parent_child) ? new_child_parent_child : child_parent_child;
		}
		if (child_parent_child > *longest) *longest = child_parent_child;
	}
}

int longestConsecutive(struct TreeNode* root)
{
	if (!root) return 0;
	if (!root->left && !root->right) return 1;
	int longest = 1, curr_longest_descending_inc = 1, curr_longest_descending_not_inc;
	longest_recursive(root, &longest, &curr_longest_descending_inc, &curr_longest_descending_not_inc, 1);
	curr_longest_descending_inc = 1;
	curr_longest_descending_not_inc = 1;
	longest_recursive(root, &longest, &curr_longest_descending_inc, &curr_longest_descending_not_inc, -1);
	return longest;
}

struct TreeNode * tree_from_int(int val)
{
	struct TreeNode * res = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	memset(res, 0, sizeof(struct TreeNode));
	res->val = val;
	return res;
}

struct TreeNode* tree_from_string(char * s)
{
	queue q;
	q.arr = (struct TreeNode **) malloc(256*sizeof(struct TreeNode*));
	q.first = 0;
	q.last = 0;
	char * tokenizer = strtok(s, ",");
	struct TreeNode * res = tree_from_int(atoi(tokenizer));
	enqueue(&q, res);
	while (tokenizer)
	{
		struct TreeNode *curr = dequeue(&q);
		tokenizer = strtok(NULL, ",");
		if (!tokenizer) break;
		curr->left = (strncmp(tokenizer, "null", 4) == 0) ? NULL : tree_from_int(atoi(tokenizer));
		tokenizer = strtok(NULL, ",");
		if (!tokenizer) break;
		curr->right = (strncmp(tokenizer, "null", 4) == 0) ? NULL : tree_from_int(atoi(tokenizer));
		if (curr->left) enqueue(&q, curr->left);
		if (curr->right) enqueue(&q, curr->right);
	}
	free(q.arr);
	return res;
}

int main()
{
	char a[]= "-33,-34,-32,-35,-35,-33,-31,-36,-36,-36,null,-32,-34,-30,-30,-37,-35,-37,-35,null,-35,null,-31,null,-35,-29,-29,-29,-31,null,-36,null,null,null,-38,null,null,null,null,null,-32,null,-36,null,-28,-30,-28,null,-28,-32,-30,null,-37,-39,null,-33,-31,null,null,-27,-27,null,-29,null,null,null,-27,-31,-31,-31,-31,null,null,-40,null,null,-34,-32,-30,-28,-26,-28,-26,null,null,null,null,null,-32,null,-32,-32,-30,null,null,-41,null,-33,null,null,-33,null,-29,-29,null,-27,null,-27,-27,-25,-25,null,null,-33,null,null,null,-31,null,null,null,null,null,null,null,null,null,null,null,-26,null,-28,-28,-28,-28,null,-26,-26,-24,null,-34,null,null,-27,-25,-29,null,-27,-27,null,null,null,-29,null,null,null,null,null,null,-35,null,-26,null,-26,-26,null,null,null,null,-26,null,null,null,-36,null,null,null,null,-27,-27,-27,-27,null,null,null,null,null,-28,-26,null,null,null,null,null,null,null,-25,-26";

	struct TreeNode * tree = tree_from_string(a);
	int longest = longestConsecutive(tree);
	printf("longest consecutive sequence is %d.\n", longest);
	return 0;
}

