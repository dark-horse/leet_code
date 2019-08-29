/*
 *
 * https://leetcode.com/problems/permutation-in-string/
 * Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.
 * Example 1:  Input: s1 = "ab" s2 = "eidbaooo" Output: True
 * Explanation: s2 contains one permutation of s1 ("ba").
 * Example 2: Input:s1= "ab" s2 = "eidboaoo" Output: False
 * Note:
 * The input strings only contain lower case letters.
 * The length of both given strings is in range [1, 10,000].
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


#define alphabet_sz (26)
#define index_from_char(ch) ( (int) (ch-'a') )

void string_checksums(char * s, int s_sz, int * c1, int *c2, int *c3)
{
	*c1 = 0; *c2 = 0; *c3 = 0;
	for (int i = 0; i < s_sz; i ++)
	{
		int int_from_ch = index_from_char(s[i]);
		*c1 = *c1 + int_from_ch;
		*c2 = *c2 + int_from_ch * int_from_ch;
		*c3 = *c3 + int_from_ch * int_from_ch * int_from_ch;
	}
}

bool check_permutation(int * s1_chars, int * s2_chars)
{
	for (int i = 0; i < alphabet_sz; i ++)
	{
		if (s1_chars[i] != s2_chars[i]) return false;
	}
	return true;
}

bool string_contains_char(char * s, char ch)
{
	for (;*s;s++)
	{
		if (*s == ch) return true;
	}
	return false;
}

/* on leetcode, not using checksums actually speeds up the process. interesting.... */
bool checkInclusion(char * s1, char * s2)
{
	if (!s1 ||!s2) return false;
	int s1_len = strlen(s1), s2_len = strlen(s2);
	if (s1_len > s2_len) return false;
	if (s1_len == 1) return string_contains_char(s2, *s1);

	int s1_chars[alphabet_sz], s2_chars[alphabet_sz];
	memset(s1_chars, 0, sizeof(int) * alphabet_sz);
	memset(s2_chars, 0, sizeof(int) * alphabet_sz);
	for (int i = 0; i < s1_len; i ++)
	{
		char ch = s1[i];
		s1_chars[index_from_char(ch)] = s1_chars[index_from_char(ch)] + 1;
		ch = s2[i];
		s2_chars[index_from_char(ch)] = s2_chars[index_from_char(ch)] + 1;
	}
	int c1_perm, c2_perm, c3_perm, c1_sliding_window, c2_sliding_window, c3_sliding_window;
	string_checksums(s1, s1_len, &c1_perm, &c2_perm, &c3_perm);
	string_checksums(s2, s1_len, &c1_sliding_window, &c2_sliding_window, &c3_sliding_window);
	if (c1_perm == c1_sliding_window && c2_perm == c2_sliding_window && c3_perm == c3_sliding_window && check_permutation(s1_chars, s2_chars))
	{
		return true;
	}
	for (int i = s1_len; i < s2_len; i ++)
	{
		int old_char = index_from_char(s2[i-s1_len]);
		int new_char = index_from_char(s2[i]);
		c1_sliding_window = c1_sliding_window - old_char + new_char;
		c2_sliding_window = c2_sliding_window - old_char*old_char + new_char*new_char;
		c3_sliding_window = c3_sliding_window - old_char*old_char*old_char + new_char*new_char*new_char;
		s2_chars[old_char] = s2_chars[old_char] - 1;
		s2_chars[new_char] = s2_chars[new_char] + 1;
		if (c1_perm == c1_sliding_window && c2_perm == c2_sliding_window && c3_perm == c3_sliding_window && check_permutation(s1_chars, s2_chars))
		{
			return true;
		}
	}
	return false;
}


int main()
{
	bool res = checkInclusion("ab", "eidbaooo");
	printf("first result is %s.\n", res ? "TRUE" : "FALSE");
	res = checkInclusion("ab", "eidboaoo");
	printf("first result is %s.\n", res ? "TRUE" : "FALSE");
	return 0;
}
