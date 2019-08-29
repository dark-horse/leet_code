/*
 *
 * https://leetcode.com/problems/add-two-numbers-ii/
 * You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 * Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 8 -> 0 -> 7
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

typedef struct stack_t
{
	int * arr;
	int arr_capacity;
	int top;
} stack;

void push(stack * s, int val)
{
	if (s->arr_capacity == s->top)
	{
		s->arr_capacity += 32;
		s->arr = realloc(s->arr, s->arr_capacity * sizeof(int));
	}
	s->arr[s->top] = val;
	s->top = s->top + 1;
}

bool is_empty(stack *s)
{
	return s->top == 0;
}

int pop(stack *s)
{
	if (!s->arr || !s->top) return 0;	/* what an appropriate error code when the stack is empty? */
	s->top = s->top - 1;
	return s->arr[s->top];
}

void free_stack(stack *s)
{
	if (!s->arr) return;
	free(s->arr);
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	if (!l1) return l2;
	if (!l2) return l1;
	stack l1_stack, l2_stack;
	l1_stack.arr = NULL; l1_stack.top = 0; l1_stack.arr_capacity = 0;
	l2_stack.arr = NULL; l2_stack.top = 0; l2_stack.arr_capacity = 0;
	while (l1)
	{
		push(&l1_stack, l1->val);
		l1 = l1->next;
	}
	while (l2)
	{
		push(&l2_stack, l2->val);
		l2 = l2->next;
	}
	int carry_over = 0;
	struct ListNode * res = NULL;
	while (!is_empty(&l1_stack) || !is_empty(&l2_stack))
	{
		int l1_int = pop(&l1_stack);
		int l2_int = pop(&l2_stack);
		int sum = l1_int + l2_int + carry_over;
		carry_over = sum / 10;
		struct ListNode * node = (struct ListNode *) malloc(sizeof(struct ListNode));
		node->val = sum % 10;
		node->next = res;
		res = node;
	}
	stack left_over_stack = is_empty(&l1_stack) ? l2_stack : l1_stack;
	while (!is_empty(&left_over_stack))
	{
		int digit = pop(&left_over_stack);
		int sum = digit + carry_over;
		carry_over = sum / 10;
		struct ListNode * node = (struct ListNode *) malloc(sizeof(struct ListNode));
		node->val = sum % 10;
		node->next = res;
		res = node;		
	}
	if (carry_over)
	{
		struct ListNode * node = (struct ListNode *) malloc(sizeof(struct ListNode));
		node->val = carry_over;
		node->next = res;
		res = node;				
	}

	free_stack(&l1_stack);
	free_stack(&l2_stack);

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
#if 0
	struct ListNode * l1 = (struct ListNode*) malloc(sizeof(struct ListNode));
	l1->val = 5;
	l1->next = NULL;

	struct ListNode * l2 = (struct ListNode*) malloc(sizeof(struct ListNode));
	l2->val = 5;
	l2->next = NULL;
#endif
	print_list(l2);
	struct ListNode * res = addTwoNumbers(l1,l2);
	print_list(res);
	free_list(l1);
	free_list(l2);
	free_list(res);
	return 0;
}
