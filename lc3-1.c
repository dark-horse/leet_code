/*
 *
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
 * Example:
 * Input:
 * [
 *  1->4->5,
 *  1->3->4,
 *  2->6
 * ]
 * Output: 1->1->2->3->4->4->5->6
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
     int val;
     struct ListNode *next;
};


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
	if (!lists || !listsSize) return NULL;
	struct ListNode ** curr_pointers = (struct ListNode**) malloc(listsSize * sizeof(struct ListNode*));
	for (int i = 0; i < listsSize; i ++)
	{
		curr_pointers[i] = lists[i];
	}
	struct ListNode * res = NULL, *res_tail = NULL;
	while(1)
	{
		struct ListNode * min_ptr = NULL;
		int min_ptr_index = 0;
		int min_value = INT_MAX;
		for (int i = 0; i < listsSize; i ++)
		{
			if (curr_pointers[i] && curr_pointers[i]->val < min_value)
			{
				min_ptr_index = i;
				min_ptr = curr_pointers[i];
				min_value = curr_pointers[i]->val;
			}
		}
		if (!min_ptr) break;	/*no more pointers to search */
		curr_pointers[min_ptr_index] = min_ptr->next;
		/* insert the min_ptr into the result */
		min_ptr->next = NULL;
		if (!res)
		{
			res = min_ptr;
		}
		else
		{
			res_tail->next = min_ptr;
		}
		res_tail = min_ptr;
	}
	free(curr_pointers);
	return res;
}

void print_linked_list(struct ListNode * l)
{
	while (l)
	{
		printf(" %d",l->val);
		l = l->next;
	}
	printf("\n");
}
void free_linked_list(struct ListNode *l)
{
	while (l)
	{
		struct ListNode * curr = l;
		l = l->next;
		free(curr);
	}
}

int main()
{
	struct ListNode * l1 = (struct ListNode *) malloc(sizeof(struct ListNode));
	l1->val = 1;
	l1->next = (struct ListNode *) malloc(sizeof(struct ListNode));
	l1->next->val = 4;
	l1->next->next = (struct ListNode *) malloc(sizeof(struct ListNode));
	l1->next->next->val = 5;
	l1->next->next->next = NULL;

	struct ListNode * l2 = (struct ListNode *) malloc(sizeof(struct ListNode));
	l2->val = 1;
	l2->next = (struct ListNode *) malloc(sizeof(struct ListNode));
	l2->next->val = 3;
	l2->next->next = (struct ListNode *) malloc(sizeof(struct ListNode));
	l2->next->next->val = 4;
	l2->next->next->next = NULL;

	struct ListNode * l3 = (struct ListNode *) malloc(sizeof(struct ListNode));
	l3->val = 2;
	l3->next = (struct ListNode *) malloc(sizeof(struct ListNode));
	l3->next->val = 6;
	l3->next->next = NULL;

	printf("print the first list\n");
	print_linked_list(l1);

	printf("print the second list\n");
	print_linked_list(l2);

	printf("print the third list\n");
	print_linked_list(l3);


	struct ListNode * lists_arr[3];
	lists_arr[0] = l1; lists_arr[1] = l2; lists_arr[2] = l3;
	struct ListNode * res = mergeKLists(lists_arr, 3);
	printf("result of mergeKLists\n");
	print_linked_list(res);

	free(res);
	return 0;
}

