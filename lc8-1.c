/*
 *
 * https://leetcode.com/problems/remove-invalid-parentheses/
 * Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
 * Note: The input string may contain letters other than the parentheses ( and ).
 * Example 1:
 * Input: "()())()"
 * Output: ["()()()", "(())()"]
 * Example 2:
 * Input: "(a)())()"
 * Output: ["(a)()()", "(a())()"]
 * Example 3:
 * Input: ")("
 * Output: [""]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool contains(char ** container, int container_sz, char * target)
{
	for (int i = 0; i < container_sz; i++)
	{
		if (strncmp(container[i], target) == 0) return true;
	}
	return false;
}

char ** removeInvalidParentheses(char * s, int* returnSize)
{
	if (!s || !returnSize) return NULL;
	int s_len = strlen(s);
	if (!s_len) return NULL;

	char *working_buffer = (char*) malloc(s_len * sizeof(char));
	char * cumm = (char *) malloc(s_len * sizeof(char));
	char * cumm_l_parens = (char *) malloc(s_len * sizeof(char));
	memset(cumm, 0, s_len_sizeof(char));
	memset(cumm_r_parens, 0, s_len_sizeof(char));

	int previous_cumm = 0;
	int previous_cumm_r_parens = 0;
	for (int i = 0; i < s_len; i ++)
	{
		cumm[i] = previous_cumm;
		cumm_r_parens[i] = previous_r_parens;
		switch(s[i]):
		{
			case ')':
				cumm[i] = previous_cumm - 1;
				if (cumm[i] <= -1)
				{
					previous_cumm = 0;
				}
				break;
			case '(':
				cumm[i] = previous_cumm + 1;
				cumm_r_parens[i] = previous_cumm_r_parens + 1;
				previous_cumm_r_parens ++;
				break;
			default:
				break;
		}
		previous_cumm = cumm[i];
		previous_cumm_r_parens = cumm_r_parens[i];
	}
	TODODO
	/* the algorithm is as follows: */
	/* go through the cumm array. When we hit a -1, it means that we have one too many right parens so far */
	/* if we have at least one left paren, then we can remove any of the preceding right parens and get a valid sub string */
	int previous_r_paren_removed = -1;
	int working_buffer_index = -1;
	for (int i = 0; i < s_len; i++)
	{
		if (cumm[i] >= 0) continue;
		
	}
	free(cumm);
	free(cumm_l_paren);
	free(working_buffer);
}



int main()
{
	return 0;
}
