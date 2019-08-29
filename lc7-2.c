/*
 *
 * https://leetcode.com/problems/add-two-numbers/
 * You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 * Example:  Input: (2 -> 4 -> 3) + (5 -> 6 -> 4) Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	int carry_over = 0;
	struct ListNode * res = NULL, *tail = NULL;
	while (l1 || l2)
	{
		struct ListNode* new_node = (struct ListNode*) malloc(sizeof(struct ListNode));
		new_node->next = NULL;
		if (tail==NULL)
		{
			res = new_node;
		}
		else
		{
			tail->next = new_node;
		}
		tail = new_node;
		int digit = carry_over;
		if (l1)
		{
			digit += l1->val;
			l1 = l1->next;
		}
		if (l2)
		{
			digit += l2->val;
			l2 = l2->next;
		}
		new_node->val = digit % 10;
		carry_over = digit / 10;
	}
	if (carry_over)
	{
		struct ListNode * new_node = (struct ListNode*) malloc(sizeof(struct ListNode));
		new_node->next = NULL;
		new_node->val = carry_over;
		tail->next = new_node;
	}
	return res;
}

void print_list(struct ListNode * l)
{
	if (!l) return;
	printf("%d", l->val);
	l = l->next;
	while (l)
	{
		printf(" -> %d", l->val);
		l = l->next;
	}
	printf("\n");
}

void free_list(struct ListNode * l)
{
	while (l)
	{
		struct ListNode* curr = l;
		l = l->next;
		free(curr);
	}
}

int main()
{
#if 0
	/* first number */
	struct ListNode * l1 = (struct ListNode*) malloc(sizeof(struct ListNode));
	l1->val = 2;
	l1->next = (struct ListNode*) malloc(sizeof(struct ListNode));
	l1->next->val = 4;
	l1->next->next = (struct ListNode*) malloc(sizeof(struct ListNode));
	l1->next->next->val = 3;
	l1->next->next->next = NULL;
	print_list(l1);

	struct ListNode * l2 = (struct ListNode*) malloc(sizeof(struct ListNode));
	l2->val = 5;
	l2->next = (struct ListNode*) malloc(sizeof(struct ListNode));
	l2->next->val = 6;
	l2->next->next = (struct ListNode*) malloc(sizeof(struct ListNode));
	l2->next->next->val = 4;
	l2->next->next->next = (struct ListNode*) malloc(sizeof(struct ListNode));
	l2->next->next->next->val = 1;
	l2->next->next->next->next = NULL;
#endif
	struct ListNode * l1 = (struct ListNode*) malloc(sizeof(struct ListNode));
	l1->val = 5;
	l1->next = NULL;

	struct ListNode * l2 = (struct ListNode*) malloc(sizeof(struct ListNode));
	l2->val = 5;
	l2->next = NULL;
	print_list(l2);
	struct ListNode * res = addTwoNumbers(l1,l2);
	print_list(res);
	free_list(l1);
	free_list(l2);
	free_list(res);
	return 0;
}
