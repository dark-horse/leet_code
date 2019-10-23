/*
 * https://leetcode.com/problems/closest-binary-search-tree-value-ii/
 * Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.
 * Note: Given target value is a floating point. You may assume k is always valid, that is: k ≤ total nodes.
 * You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
 * Example:
 * Input: root = [4,2,5,1,3], target = 3.714286, and k = 2
 * 
 *     4
 *   / \
 *  2   5
 * / \
 *1   3
 * Output: [4,3]
 * Follow up: Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?
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

#define abs(a) ( ((a) < 0) ? (0 - (a)) : (a) )

typedef struct heap_node_t
{
	float dist;
	int tree_val;
} heap_node;

void swap_heap_nodes(heap_node * heap, int index_a, int index_b)
{
	heap_node tmp = heap[index_a];
	heap[index_a] = heap[index_b];
	heap[index_b] = tmp;
}

void add_to_heap(heap_node * heap, int * heap_count, float dist, int tree_val)
{
	int insert_index = *heap_count;
	*heap_count = insert_index + 1;
	heap[insert_index].dist = dist;
	heap[insert_index].tree_val = tree_val;
	/* bubble up if necessary */
	while (insert_index)
	{
		int parent_index = (insert_index - 1) / 2;
		if (heap[parent_index].dist > heap[insert_index].dist) break;
		swap_heap_nodes(heap, parent_index, insert_index);
		insert_index = parent_index;
	}
}

void replace_heap_top(heap_node * heap, int heap_sz, float new_dist, int tree_val)
{
	heap[0].dist = new_dist;
	heap[0].tree_val = tree_val;
	/* bubble down if necessary */
	int parent_index = 0;
	while (parent_index < heap_sz)
	{
		int l_child_index = 2 * parent_index + 1;
		int r_child_index = 2 * parent_index + 2;
		if (l_child_index >= heap_sz) break;
		int swap_index = parent_index;
		if (heap[l_child_index].dist > heap[parent_index].dist) swap_index = l_child_index;
		if (r_child_index < heap_sz && heap[r_child_index].dist > heap[l_child_index].dist) swap_index = r_child_index;
		if (heap[parent_index].dist >= heap[swap_index].dist) break;
		swap_heap_nodes(heap, parent_index, swap_index);
		parent_index = swap_index;
	}
}

void closestKValues_float(struct TreeNode* root, float target, int k, heap_node * heap, int * heap_count)
{
	if (!root) return;
	float new_dist = abs(root->val - target);
	if (*heap_count < k)
	{
		add_to_heap(heap, heap_count, new_dist, root->val);
	}
	else if (new_dist < heap[0].dist)
	{
		replace_heap_top(heap, k, new_dist, root->val);
	}
	closestKValues_float(root->left, target, k, heap, heap_count);
	closestKValues_float(root->right, target, k, heap, heap_count);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestKValues(struct TreeNode* root, double target, int k, int* returnSize)
{
	heap_node * heap = (heap_node*) malloc(sizeof(heap_node) * k);
	int heap_count = 0;
	closestKValues_float(root, target, k, heap, &heap_count);

	int * res = (int *) malloc(sizeof(int) * k);
	for (int i = 0; i < k; i ++)
	{
		res[i] = heap[i].tree_val;
	}

	free(heap);
	*returnSize = k;
	return res;
}


struct TreeNode * node_from_val(int val)
{
	struct TreeNode * res = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	res->val = val;
	res->left = NULL;
	res->right = NULL;
	return res;
}

void print_int_arr(int * arr, int arr_sz)
{
	if (!arr || !arr_sz) return;
	printf("[%d",arr[0]);
	for (int i = 1; i < arr_sz; i ++)
	{
		printf(",%d", arr[i]);
	}
	printf("]\n");
}

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

struct TreeNode* tree_from_string(char * s)
{
	queue q;
	q.arr = (struct TreeNode **) malloc(256*sizeof(struct TreeNode*));
	q.first = 0;
	q.last = 0;
	char * tokenizer = strtok(s, ",");
	struct TreeNode * res = node_from_val(atoi(tokenizer));
	enqueue(&q, res);
	while (tokenizer)
	{
		struct TreeNode *curr = dequeue(&q);
		tokenizer = strtok(NULL, ",");
		if (!tokenizer) break;
		curr->left = (strncmp(tokenizer, "null", 4) == 0) ? NULL : node_from_val(atoi(tokenizer));
		tokenizer = strtok(NULL, ",");
		if (!tokenizer) break;
		curr->right = (strncmp(tokenizer, "null", 4) == 0) ? NULL : node_from_val(atoi(tokenizer));
		if (curr->left) enqueue(&q, curr->left);
		if (curr->right) enqueue(&q, curr->right);
	}
	free(q.arr);
	return res;
}

/*
[2,0,33,null,1,25,40,null,null,11,31,34,45,10,18,29,32,null,36,43,46,4,null,12,24,26,30,null,null,35,39,42,44,null,48,3,9,null,14,22,null,null,27,null,null,null,null,38,null,41,null,null,null,47,49,null,null,5,null,13,15,21,23,null,28,37,null,null,null,null,null,null,null,null,8,null,null,null,17,19,null,null,null,null,null,null,null,7,null,16,null,null,20,6]
2.428571
14
*/
int main()
{
	struct TreeNode * root = node_from_val(4);
	root->right = node_from_val(5);
	root->left = node_from_val(2);
	root->left->left = node_from_val(1);
	root->left->right = node_from_val(3);
	int * res, res_sz;
	res = closestKValues(root, 4.714286, 2, &res_sz);
	print_int_arr(res, res_sz);
	char test[] = "2,0,33,null,1,25,40,null,null,11,31,34,45,10,18,29,32,null,36,43,46,4,null,12,24,26,30,null,null,35,39,42,44,null,48,3,9,null,14,22,null,null,27,null,null,null,null,38,null,41,null,null,null,47,49,null,null,5,null,13,15,21,23,null,28,37,null,null,null,null,null,null,null,null,8,null,null,null,17,19,null,null,null,null,null,null,null,7,null,16,null,null,20,6";
	struct TreeNode * test_tree = tree_from_string(test);
	res = closestKValues(test_tree, 2.428571, 14, &res_sz);
	print_int_arr(res, res_sz);
	return 0;
}

