/*
 *
 * https://leetcode.com/problems/longest-valid-parentheses/
 * Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 * Example 1: Input: "(()" Output: 2 Explanation: The longest valid parentheses substring is "()"
 * Example 2: Input: ")()())" Output: 4 Explanation: The longest valid parentheses substring is "()()"
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct balanced_parens_block_t
{
	int start;
	int end;
} balanced_parens_block;

typedef struct stack_block_t
{
	int capacity;
	int size;
	balanced_parens_block * arr;
} stack_block;

void push_stack_block(stack_block * s, balanced_parens_block val)
{
	s->size ++;
	if (s->size >= s->capacity)
	{
		s->capacity = s->capacity ? s->capacity * 2 : 64;
		s->arr = realloc(s->arr, s->capacity * sizeof(balanced_parens_block));
	}
	s->arr[s->size-1] = val;
}

bool is_empty_stack_block(stack_block *s)
{
	return s->size == 0;
}

balanced_parens_block pop_stack_block(stack_block * s)
{
	if (s->size)
	{
		s->size --;
		return s->arr[s->size];
	}
	balanced_parens_block res;
	return res; /*what's a good error code in this situation? */
}

balanced_parens_block peek_stack_block(stack_block * s)
{
	if (s->size)
	{
		return s->arr[s->size-1];
	}
	balanced_parens_block res;
	return res; /*what's a good error code in this situation? */
}


void free_stack_block(stack_block *s)
{
	if (s->capacity) free(s->arr);
	memset(s, 0, sizeof(balanced_parens_block));
}


typedef struct stack_int_t
{
	int capacity;
	int size;
	int * arr;
} stack_int;

void push_stack_int(stack_int * s, int val)
{
	s->size ++;
	if (s->size >= s->capacity)
	{
		s->capacity = s->capacity ? s->capacity * 2 : 64;
		s->arr = realloc(s->arr, s->capacity * sizeof(int));
	}
	s->arr[s->size-1] = val;
}

bool is_empty_stack_int(stack_int *s)
{
	return s->size == 0;
}

int pop_stack_int(stack_int * s)
{
	if (s->size)
	{
		s->size --;
		return s->arr[s->size];
	}
	return -1; /*what's a good error code in this situation? */
}

void free_stack_int(stack_int *s)
{
	if (s->capacity) free(s->arr);
	memset(s, 0, sizeof(stack_int));
}

int longestValidParentheses(char * s)
{
	if (!s || !(*s) || !(*(s+1))) return 0;
	int max_parens_beg = -1, max_parens_end = -1, current_parens_beg = -1, current_parens_end = -1;
	stack_int stck;
	memset(&stck, 0, sizeof(stack_int));
	stack_block block_stack;
	memset(&block_stack, 0, sizeof(stack_block));
	for (int i = 0; s[i]; i ++)
	{
		char ch = s[i];
		if (ch == '(')
		{
			push_stack_int(&stck, i);
			continue;
		}
		/* ch must be ')'*/
		if (is_empty_stack_int(&stck)) continue;
		current_parens_beg = pop_stack_int(&stck);
		current_parens_end = i;

		while (!is_empty_stack_block(&block_stack))
		{
			balanced_parens_block previous_block = peek_stack_block(&block_stack);
			if (previous_block.start > current_parens_beg)
			{
				pop_stack_block(&block_stack);
				continue;
			}
			if (previous_block.end == current_parens_beg-1)
			{
				current_parens_beg = previous_block.start;
				pop_stack_block(&block_stack);
				continue;
			}
			break;
		}
		if (current_parens_end - current_parens_beg > max_parens_end - max_parens_beg)
		{
			max_parens_end = current_parens_end;
			max_parens_beg = current_parens_beg;
		}
		balanced_parens_block block;
		block.start = current_parens_beg;
		block.end = current_parens_end;
		push_stack_block(&block_stack, block);
	}
	free_stack_int(&stck);
	return max_parens_end != -1 ? max_parens_end - max_parens_beg + 1 : 0;
}



int main()
{
	printf("longest valid parentheses lengths is %d. should be 2\n", longestValidParentheses("(()"));
	printf("longest valid parentheses lengths is %d. should be 4\n", longestValidParentheses(")()())"));
	printf("longest valid parentheses lengths is %d. should be 8\n", longestValidParentheses("((())())"));
	printf("longest valid parentheses lengths is %d. should be 4\n", longestValidParentheses("((())"));
	printf("longest valid parentheses lengths is %d. should be 4\n", longestValidParentheses("((()()"));
	printf("longest valid parentheses lengths is %d. should be 8\n", longestValidParentheses("(()(()))"));
	printf("longest valid parentheses lengths is %d. should be 8\n", longestValidParentheses("((())))()()()()"));
	printf("longest valid parentheses lengths is %d. should be 8\n", longestValidParentheses("((())))()()()())"));
	printf("longest valid parentheses lengths is %d. should be 8\n", longestValidParentheses(")())(()((((()))))()()))))(()()()))))(()(((())((((()))((((((()((())))))())(((((((()))))((((()((())))(())))))((((()(())())())(()))((()))())())()))))()))()"));
	printf("longest valid parentheses lengths is %d. should be 0\n", longestValidParentheses(")("));
	printf("longest valid parentheses lengths is %d. should be 6\n", longestValidParentheses("()(())"));
	printf("longest valid parentheses lengths is %d. should be 8\n", longestValidParentheses("()(())()"));
	return 0;
}
