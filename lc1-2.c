/*
 *
 * https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
 * Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.
 * Example 1: Input: "eceba" Output: 3 Explanation: t is "ece" which its length is 3.
 * Example 2: Input: "ccaabbb" Output: 5 Explanation: t is "aabbb" which its length is 5.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


int lengthOfLongestSubstringTwoDistinct(char * s)
{
	/* some base cases */
	if (!s) return 0;
	int s_len = strlen(s);
	if (s_len<=2) return s_len;

	char char_1 = s[0], char_2 = s[1];
	int res_beg = 0, res_end = 1, candidate_beg = 0;
	while (s[res_end] && s[res_end] == s[res_beg])
	{
		res_end ++;
	}
	if (!s[res_end]) return res_end-res_beg;
	char_2 = s[res_end];
	int candidate_end = res_end;

	/* keep the index of the previous character so we don't have to search back */
	int index_of_previous_character = res_end;
	for (int i = res_end+1; s[i]; i ++)
	{
		char ch = s[i];
		if (ch == char_1 || ch == char_2)
		{
			candidate_end = i;
			if (s[index_of_previous_character] != s[i]) index_of_previous_character = i;
			continue;
		}
		if (candidate_end - candidate_beg > res_end - res_beg)
		{
			res_end = candidate_end;
			res_beg = candidate_beg;
		}
		candidate_end = i;
		candidate_beg = index_of_previous_character;
		index_of_previous_character = i;
		/*
		candidate_beg = i-1;
		while (candidate_beg > 0 && s[candidate_beg-1] == s[i-1])
		{
			candidate_beg --;
		}
		*/
		char_1 = s[candidate_beg];
		char_2 = s[candidate_end];
	}
	return (candidate_end - candidate_beg > res_end-res_beg) ? candidate_end-candidate_beg +1 : res_end-res_beg + 1;
}



int main()
{
	printf("longest length for string eceba is %d.\n", lengthOfLongestSubstringTwoDistinct("eceba"));

	printf("longest length for string ccaabbb is %d.\n", lengthOfLongestSubstringTwoDistinct("ccaabbb"));
	printf("longest length for string cdaba is %d.\n", lengthOfLongestSubstringTwoDistinct("cdaba"));

	return 0;
}
