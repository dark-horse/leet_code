/*
 *
 * https://leetcode.com/problems/copy-list-with-random-pointer/
 * A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
 * Return a deep copy of the list.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node_t {
	int val;
	struct Node_t* next;
	struct Node_t* random;
} Node;

#define undef_ptr ((Node*) -1)

typedef struct hash_node_t
{
	Node * key;
	Node * val;
	struct hash_node_t * next;
} hash_node;

void init_hash(hash_node * arr, int arr_sz)
{
	for (int i = 0; i < arr_sz; i++)
	{
		hash_node * curr = arr + i;
		curr->key = undef_ptr;
		curr->val = undef_ptr;
		curr->next = NULL;
	}
}

void insert_hash(hash_node * arr, int arr_sz, Node * key, Node * val)
{
	int hash_pos = ((int) key) % arr_sz;
	if (hash_pos < 0) hash_pos = 0 - hash_pos;
	hash_node * curr = arr + hash_pos;
	if (curr->key == undef_ptr)
	{
		curr->key = key;
		curr->val = val;
	}
	else
	{
		hash_node * node = (hash_node*) malloc(sizeof(hash_node));
		node->next = curr->next;
		node->key = key;
		node->val = val;
		curr->next = node;
	}
}

Node * get_val_for_key(hash_node * arr, int arr_sz, Node * key)
{
	int hash_pos = ((int) key) % arr_sz;
	if (hash_pos < 0) hash_pos = 0 - hash_pos;
	hash_node * curr = arr + hash_pos;
	while (curr->key != key)
	{
		curr = curr->next;
	}
	return curr ? curr->val : undef_ptr;
}

void free_hash(hash_node * arr, int arr_sz)
{
	for (int i = 0; i < arr_sz; i++)
	{
		hash_node * curr = arr + i;
		curr = curr->next;
		while (curr)
		{
			hash_node * next = curr->next;
			free(curr);
			curr = next;
		}
	}
}

Node* copyRandomList(Node* head)
{
	if (!head) return NULL;
	/* find the length of the list */
	int list_len = 0;
	Node * curr = head;
	while (curr)
	{
		list_len ++;
		curr = curr->next;
	}
	int hash_tbl_sz = list_len + 10 + list_len / 5;	/* around 80% occupancy ratio */
	hash_node * hash_tbl = (hash_node *) malloc(sizeof(hash_node) * hash_tbl_sz);
	init_hash(hash_tbl, hash_tbl_sz);
	Node * res = (Node*) malloc(sizeof(Node));
	res->val = head->val;
	res->next = NULL;
	res->random = head->random;
	insert_hash(hash_tbl, hash_tbl_sz, head, res);
	Node * tail = res;
	curr = head->next;
	while (curr)
	{
		Node * node = (Node*) malloc(sizeof(Node));
		node->val = curr->val;
		node->random = curr->random;
		node->next = NULL;
		tail->next = node;
		tail = node;
		insert_hash(hash_tbl, hash_tbl_sz, curr, node);
		curr = curr->next;
	}
	curr = res;
	while (curr)
	{
		if (curr->random)
		{
			curr->random = get_val_for_key(hash_tbl, hash_tbl_sz, curr->random);
		}
		curr = curr->next;
	}

	free_hash(hash_tbl, hash_tbl_sz);
	free(hash_tbl);
	return res;
}

void print_list(Node * list)
{
	while (list)
	{
		printf("value %d and value of random pointer is ", list->val);
		if (list->val)
		{
			printf("%d.\n", list->random->val);
		}
		else
		{
			printf("NULL.\n");
		}
		list = list->next;
	}
}

int main()
{
	Node * head = (Node *) malloc(sizeof(Node));
	head->val = 1;
	Node * next = (Node *) malloc(sizeof(Node));
	next->val = 2;
	next->next = NULL;
	next->random = next;
	head->next = next;
	head->random = next;
	print_list(head);
	Node * res = copyRandomList(head);
	print_list(res);
	return 0;
}
