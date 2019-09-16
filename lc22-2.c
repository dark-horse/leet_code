/*
 *
 * https://leetcode.com/problems/longest-palindromic-substring/
 * Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 * Example 1:  Input: "babad" Output: "bab" Note: "aba" is also a valid answer.
 * Example 2:  Input: "cbbd" Output: "bb"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(char * start, char * end)
{
	while (start < end)
	{
		if (*start != *end) return false;
		start ++;
		end--;
	}
	return true;
}

int longest_palindrome_centered(char * s, int center, char * end)
{
	int res = 1;
	char * pal_start = s + center - 1, * pal_end = s + center + 1;
	while (pal_start >= s && pal_end <= end && (*pal_start) == (*pal_end))
	{
		res += 2;
		pal_start --;
		pal_end ++;
	}
	return res;
}

/* PRECONDITION: center2 == center1 + 1 */
int longest_palindrome_two_centers(char * s, int center1, int center2, char * end)
{
	int res = 0;
	char * pal_start = s+center1, * pal_end = s + center2;
	while (pal_start >= s && pal_end <= end && (*pal_start == *pal_end))
	{
		res += 2;
		pal_start --;
		pal_end ++;
	}
	return res;
}

char * longestPalindrome(char * s)
{
	if (!s || !(*s)) return s;
	int max_pal_start = 0, max_pal_len = 0;
	int s_len = strlen(s);
	for (int i = 0; i < s_len; i ++)
	{
		int centered_max_len = longest_palindrome_centered(s, i, s + s_len - 1);
		if (centered_max_len > max_pal_len)
		{
			max_pal_len = centered_max_len;
			max_pal_start = i - max_pal_len / 2;
		}
		int two_centered_max_len = longest_palindrome_two_centers(s, i, i + 1, s + s_len - 1);
		if (two_centered_max_len > max_pal_len)
		{
			max_pal_len = two_centered_max_len;
			max_pal_start = i - max_pal_len / 2 + 1;
		}
	}
	char * res = (char *) malloc(sizeof(char) * (max_pal_len + 1));
	memcpy(res /*dest*/, s + max_pal_start /*dest*/, max_pal_len * sizeof(char));
	res[max_pal_len] = '\0';
	return res;
}

char * longestPalindrome_slow(char * s)
{
	if (!s || !(*s)) return s;
	int s_len = strlen(s);
	/* look for the longest palindrome backwards */
	/* it is brute force approach ..... */
	int max_palindrome_len = s_len, max_palindrome_index = 0;
	for (; ; max_palindrome_len --)
	{
		bool found_palindrome = false;
		for (int j = 0; j <= s_len - max_palindrome_len; j++)
		{
			if (is_palindrome(s+j, s+j+max_palindrome_len-1))
			{
				found_palindrome = true;
				max_palindrome_index= j;
				break;
			}
		}
		if (found_palindrome) break;
	}
	char * res = (char *) malloc(sizeof(char)*(max_palindrome_len + 1));
	memcpy(res /*dest*/, s + max_palindrome_index /*src*/, max_palindrome_len * sizeof(char));
	res[max_palindrome_len] = '\0';
	return res;
}



int main()
{
	printf("max palindrome substring for \"babad\" is \"%s\".\n",longestPalindrome("babad"));
	printf("max palindrome substring for \"cbbd\" is \"%s\".\n",longestPalindrome("cbbd"));
	return 0;
}
