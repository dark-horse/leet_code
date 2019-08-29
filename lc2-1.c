/*
 *
 * https://leetcode.com/problems/valid-parentheses/
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * An input string is valid if:
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Note that an empty string is also considered valid.
 * Example 1: 	Input: "()" 			Output: true
 * Example 2:	Input: "()[]{}"			Output: true
 * Example 3:	Input: "(]"				Output: false
 * Example 4:	Input: "([)]"			Output: false
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct stack_t
{
	int capacity;
	int used;
	char * data;
} stack;

void push(stack * s, char c)
{
	s->used ++;
	if (s->capacity <= s->used)
	{
		s->capacity = (s->capacity * 2 > s->used+1) ? s->capacity * 2 : s->used+1;
		s->data = realloc(s->data, s->capacity);
	}
	s->data[s->used-1] = c;
}
bool is_empty(stack *s)
{
	return s->used == 0;
}

char pop(stack *s)
{
	s->used --;
	return s->data[s->used];
}

void free_data(stack * s)
{
	if (s->data) free(s->data);
}

bool isValid(char * s)
{
	stack stk;
	stk.data = NULL; stk.used=0;stk.capacity=0;
	char c;
	for (;*s;s++)
	{
		switch (*s)
		{
			case '(':
				/* falling through */
			case '[':
				/* falling through */
			case '{':
				push(&stk, *s);
				break;
			case ')':
				if (is_empty(&stk)) return false;
				c = pop(&stk);
				if (c != '(') return false;
				break;
			case ']':
				if (is_empty(&stk)) return false;
				c = pop(&stk);
				if (c != '[') return false;
				break;
			case '}':
				if (is_empty(&stk)) return false;
				c = pop(&stk);
				if (c != '{') return false;
				break;
			default:
				break;
		}
	}
	bool res = is_empty(&stk);
	free_data(&stk);
	return res;
}


int main()
{
	bool res = isValid("()");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	res = isValid("()[]{}");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	res = isValid("(]");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	res = isValid("([)]");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	res = isValid("{[]}");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	res = isValid("{{[]}}");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	res = isValid("[{[]}]");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	res = isValid("[[{[]}]]");
	printf("string is valid ? %s.\n", res ? "TRUE" : "FALSE");
	return 0;
}
