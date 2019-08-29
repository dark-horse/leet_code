/*
 *
 * https://leetcode.com/problems/longest-consecutive-sequence/
 * Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 * Your algorithm should run in O(n) complexity.
 * Example:  Input: [100, 4, 200, 1, 3, 2] Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define SENTINEL_VALUE (INT_MIN)

typedef struct hash_node_t
{
	int key;
	struct hash_node_t * next;
	int seq_beg, seq_end;
} hash_node;

hash_node * hash_value(hash_node * hash_tbl, int hash_tbl_sz, int hash_key)
{
	int hash_position = hash_key % hash_tbl_sz;
	if (hash_position < 0) hash_position = 0 - hash_position;
	hash_node * node = hash_tbl+hash_position;
	while (node && node->key != hash_key)
	{
		node = node->next;
	}

	return node;
}

void free_hash_table(hash_node * hash_tbl, int hash_tbl_sz)
{
	for (int i = 0; i < hash_tbl_sz; i ++)
	{
		hash_node * node = hash_tbl + i;
		node = node->next;
		while (node)
		{
			hash_node * next = node->next;
			free(node);
			node = next;
		}
	}
}

void insert_into_hash_key_value(hash_node * hash_tbl, int hash_tbl_sz, int key, int seq_beg, int seq_end)
{
	int hash_index = key % hash_tbl_sz;
	if (hash_index < 0) hash_index = 0 - hash_index;
	if (hash_tbl[hash_index].key == SENTINEL_VALUE)
	{
		hash_tbl[hash_index].key = key;
		hash_tbl[hash_index].seq_beg = seq_beg;
		hash_tbl[hash_index].seq_end = seq_end;
	}
	else
	{
		hash_node * node = (hash_node*) malloc(sizeof(hash_node));
		node->key = key;
		node->next = hash_tbl[hash_index].next;
		hash_tbl[hash_index].next = node;
		node->seq_beg = seq_beg;
		node->seq_end = seq_end;
	}
}

int longestConsecutive(int* nums, int numsSize)
{
	/* some base cases */
	if (!nums || !numsSize) return 0;
	if (numsSize == 1) return 1;

	int hash_tbl_sz = numsSize + numsSize / 5 + 1;
	//int hash_tbl_sz = numsSize + numsSize + 1;
	hash_node * hash = (hash_node *) malloc(sizeof(hash_node) * hash_tbl_sz);
	for (int i = 0; i < hash_tbl_sz; i ++)
	{
		hash[i].next = NULL;
		hash[i].key = SENTINEL_VALUE;
		hash[i].seq_beg = SENTINEL_VALUE;
		hash[i].seq_end = SENTINEL_VALUE;
	}

	int res = 1;
	for (int i = 0; i < numsSize; i++)
	{
		hash_node * node = hash_value(hash, hash_tbl_sz, nums[i]);
		/* if this item is already in our hash continue */
		if (node) continue;

		int seq_beg = nums[i], seq_end = nums[i];
		/* see if the item below nums[i] is there */
		hash_node * before = hash_value(hash, hash_tbl_sz, nums[i]-1);
		if (before)
		{
			seq_beg = before->seq_beg;
		}
		/* see if the item after nums[i] is there */
		hash_node * after = hash_value(hash, hash_tbl_sz, nums[i]+1);
		if (after)
		{
			seq_end = after->seq_end;
		}

		/* update the beggning and ending of the new sequence */
		hash_node * seq_beg_node = hash_value(hash, hash_tbl_sz,seq_beg);
		if (seq_beg_node)
		{
			seq_beg_node->seq_beg = seq_beg;
			seq_beg_node->seq_end = seq_end;
		}
		hash_node * seq_end_node = hash_value(hash, hash_tbl_sz,seq_end);
		if (seq_end_node)
		{
			seq_end_node->seq_beg = seq_beg;
			seq_end_node->seq_end = seq_end;
		}
		insert_into_hash_key_value(hash, hash_tbl_sz, nums[i], seq_beg, seq_end);
		if (seq_end - seq_beg + 1  > res) res = seq_end - seq_beg + 1;
	}

	free_hash_table(hash, hash_tbl_sz);
	return res;
}



int main()
{
	int a[] = {100, 4, 200, 1, 3, 2, 5, 0};
	printf("longest consecutive sequence has lengths: %d.\n", longestConsecutive(a, 8));
	return 0;
}
