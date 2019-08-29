/*
 *
 * https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 * Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file
 * or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization
 * algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized
 * to the original tree structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* The format will be the following */
/* 1. The first 4 bytes will be an unsigned integer with the number of non-empty nodes in the tree */
/* 2. Each node will be stored with 5 bytes integer: */
/* 2.1. The "val" will be stored as 4 bytes integer. */
/* 2.2. We need to distinguish a NULL node. We will add 1 byte after each 4 bytes. */
/*      If the byte is 0, these 5 bytes represent a non-NULL node. Otherwise, it is a NULL node */
/* 3. The nodes will be written in prefix notation (first visit the root, then left/rigth subnodes) */

typedef struct serialized_node_t
{
	int val;
	char type;
} serialized_node;

#define ND_SZ (sizeof(serialized_node))

void serialize_prefix(struct TreeNode* root, char ** res, int * res_sz, int *res_index, unsigned int * tree_nodes_count)
{
	serialized_node s;
    if (!root)
	{
		s.val = 0;
		s.type = '\1';
	}
	else
	{
		s.val = root->val;
		s.type = '\0';
	}
	if(*res_index + ND_SZ > *res_sz)
	{
		*res_sz = *res_sz + 20 * ND_SZ;	/* make room for 10 more nodes. */
		*res = realloc(*res, *res_sz);
	}
	memcpy((*res) + *res_index /*dest*/, &s /*src*/, ND_SZ);
	*res_index = *res_index + ND_SZ;

	if (!root) return;

	*tree_nodes_count = *tree_nodes_count + 1;
	serialize_prefix(root->left, res, res_sz, res_index, tree_nodes_count);
	serialize_prefix(root->right, res, res_sz, res_index, tree_nodes_count);
}

/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root)
{
	char * res;
    if (!root)
	{
		res = (char *) malloc(sizeof(int));
		*((int*)res) = 0;
		return res;
	}
	int res_sz = sizeof(unsigned int) + 20 * ND_SZ;	/* start with room for 20 tree nodes */
	res = (char *) malloc(res_sz);
	int res_index = sizeof(unsigned int);
	unsigned int tree_nodes_count = 0;
	serialize_prefix(root, &res, &res_sz, &res_index, &tree_nodes_count);
	* ((unsigned int*) res) = tree_nodes_count;
	return res;
}

struct TreeNode * deserialize_prefix(char * data, int * data_index)
{
	serialized_node s;
	memcpy(&s /*dest*/, data + *data_index/*src*/, ND_SZ);
	*data_index = *data_index + ND_SZ;
	if (s.type == 0)
	{
		struct TreeNode * res = (struct TreeNode*) malloc(sizeof(struct TreeNode));
		res->val = s.val;
		res->left = deserialize_prefix(data, data_index);
		res->right = deserialize_prefix(data, data_index);
		return res;
	}
	else
	{
		return NULL;
	}
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data)
{
    int tree_nodes_count = * ((int*) data);
	if (!tree_nodes_count) return NULL;
	int data_index = 0;
	return deserialize_prefix(data + sizeof(unsigned int), &data_index);
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);


struct TreeNode * create_node(int val)
{
	struct TreeNode * res = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	res->val = val;
	res->left = NULL;
	res->right = NULL;
	return res;
}
bool equal_tree(struct TreeNode * a, struct TreeNode * b)
{
	if (!a || !b) return a==b;
	if (a->val != b->val) return false;
	return equal_tree(a->left, b->left) && equal_tree(a->right, b->right);
}

int main()
{
	struct TreeNode * root = create_node(10);
	//root->left = create_node(20);
	//root->left->right = create_node(30);
	//root->right = create_node(40);
	//root->right->left = create_node(50);
	//root->right->right = create_node(60);
	char * serialized_tree = serialize(root);
	struct TreeNode * deserialized_tree = deserialize(serialized_tree);
	printf("%s.\n", (equal_tree(root, deserialized_tree)) ? "SUCCESS" : "FAILURE");
	return 0;
}
