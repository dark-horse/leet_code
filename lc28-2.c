/*
 * https://leetcode.com/problems/decode-ways/
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given a non-empty string containing only digits, determine the total number of ways to decode it.
 * Example 1: Input: "12" Output: 2 Explanation: It could be decoded as "AB" (1 2) or "L" (12).
 * Example 2: Input: "226" Output: 3 Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int calculate_len_and_validate(char *s)
{
	int res = 0;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == '0' && (i == 0 || (s[i-1] != '1' && s[i-1] != '2'))) return -1;
		res ++;
	}
	return res;
}

/* s 3 or more characters */
int num_decoding_dp(char *s)
{
	int res = 0;
	int s_len = calculate_len_and_validate(s);
	if (s_len < 0) return 0;
	int two_ahead = s[s_len-1] == '0' ? 0 : 1;
	int one_ahead = ( (s[s_len-2] == '1' && s[s_len-1] >= '1') || (s[s_len-2] == '2' && s[s_len-1] <= '6' && s[s_len-1] >= '1') ) ? 2 : 1;
	for (int i = s_len-3; i >= 0; i --)
	{
		char ch = s[i];
		if ( (ch == '1' && s[i+1] >= '1' && s[i+2] != '0' ) || (ch == '2' && s[i+1] <= '6' && s[i+1] >= '1' && s[i+2] != '0') )
		{
			res = one_ahead + two_ahead;
		}
		else
		{
			res = one_ahead;
		}
		two_ahead = one_ahead;
		one_ahead = res;
	}
	return res;
}

int numDecodings(char * s)
{
	if (!s || !(*s)) return 0;
	if (!(*(s+1))) return *s == '0' ? 0 : 1;
	if (!(*(s+2)))
	{
		if (*s == '0') return 0;
		if (*s == '1') return (*(s+1) == '0') ? 1 : 2;
		if (*s == '2') return ( *(s+1) <= '6' && *(s+1) != '0') ? 2 : 1;
		if (*(s+1) == '0') return 0;
		return 1;
	}
	return num_decoding_dp(s);
}


int main()
{

	printf("%d.\n", numDecodings("101"));
	printf("%d.\n", numDecodings("110"));
	printf("%d.\n", numDecodings("1101"));
	return 0;
}

