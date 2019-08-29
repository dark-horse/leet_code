/*
 *
 * https://leetcode.com/problems/regular-expression-matching/
 * Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 * Note:
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters like . or *.
 * Example 1: Input: s = "aa" p = "a" Output: false
 * Explanation: "a" does not match the entire string "aa".
 * Example 2: Input: s = "aa" p = "a*" Output: true
 * Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
 * Example 3: Input: s = "ab" p = ".*" Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 * Example 4: Input: s = "aab" p = "c*a*b" Output: true
 * Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
 * Example 5: Input: s = "mississippi" p = "mis*is*p*." Output: false
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool is_match_recursive(char * s, char * p, int s_len, int p_len, int s_index, int p_index, int * cache)
{
	if (s_index >= s_len)
	{
		if (p_index >= p_len) return true;
		while (p_index < p_len-1)
		{
			if (p[p_index+1] == '*')
			{
				p_index += 2;
				continue;
			}
			return false;
		}
		return (p_index == p_len) ? true : false;
	}
	if (p_index >= p_len) return s_index >= s_len;
	/* cache rules: 0 means not set, -1 means false, 1 means true */
	if (cache[p_index * s_len + s_index]) return cache[p_index * s_len + s_index] == 1 ? true : false;
	bool res = false;

	if (p[p_index] == '.' || p[p_index] == s[s_index])
	{
		if (p_index < p_len - 1 && p[p_index+1] == '*')
		{
			res = is_match_recursive(s, p, s_len, p_len, s_index + 1, p_index, cache);
			res = res || is_match_recursive(s, p, s_len, p_len, s_index + 1, p_index + 2, cache);
		}
		else
		{
			res = res || is_match_recursive(s, p, s_len, p_len, s_index + 1, p_index + 1, cache);
		}
	}
	if (p_index < p_len - 1 && p[p_index+1] == '*')	
	{
		res = res || is_match_recursive(s, p, s_len, p_len, s_index, p_index + 2, cache);
	}
	cache[p_index * s_len + s_index] = res ? +1 : -1;
	return res;
}

bool isMatch(char * s, char * p)
{
	if (!p || !(*p)) return (!s || !(*s));
	if (!s || !(*s))
	{
		if (!p || !(*p)) return true;
		int p_len = strlen(p);
		int p_index = 0;
		while (p_index < p_len-1)
		{
			if (p[p_index+1] == '*')
			{
				p_index += 2;
				continue;
			}
			return false;
		}
		return (p_index == p_len) ? true : false;

	}
	int s_len = strlen(s), p_len = strlen(p);
	int * cache = (int *) malloc(s_len * p_len * sizeof(int));
	memset(cache, 0, s_len * p_len * sizeof(int));
	bool res = is_match_recursive(s, p, s_len, p_len, 0, 0, cache);
	free(cache);
	return res;
}

int main()
{
	printf("s is aa and p is a. result is %s\n", isMatch("aa", "a") ? "TRUE" : "FALSE");
	printf("s is aa and p is a*. result is %s\n", isMatch("aa", "a*") ? "TRUE" : "FALSE");
	printf("s is a and p is ab*. result is %s\n", isMatch("a", "ab*") ? "TRUE" : "FALSE");
	printf("s is aab and p is c*a*b*. result is %s\n", isMatch("aab", "c*a*b") ? "TRUE" : "FALSE");
	printf("s is bbbba and p is .*a*a. result is %s\n", isMatch("bbbba", ".*a*a") ? "TRUE" : "FALSE");
	printf("s is empty and p is .*a* result is %s\n", isMatch("", ".*a*") ? "TRUE" : "FALSE");
	printf("s is mississippi and p is mis*is*p*.. result is %s\n", isMatch("mississippi", "mis*is*p*.") ? "TRUE" : "FALSE");
	return 0;
}

