/*
 *
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * Given a string, find the length of the longest substring without repeating characters.
 * Example 1: Input: "abcabcbb" Output: 3 Explanation: The answer is "abc", with the length of 3. 
 * Example 2: Input: "bbbbb" Output: 1 Explanation: The answer is "b", with the length of 1.
 * Example 3: Input: "pwwkew" Output: 3 Explanation: The answer is "wke", with the length of 3. 
 *         Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define alphabet_sz (256)
#define index_from_char(ch) ((int) (ch-'\0'))

int lengthOfLongestSubstring(char * s)
{
	/* some base cases */
	if (!s || !(*s)) return 0;
	if (!(*s+1)) return 1;

	int occurences_count[alphabet_sz], occurences_index[alphabet_sz];
	memset(occurences_count, 0, alphabet_sz * sizeof(int));
	memset(occurences_index, 0, alphabet_sz * sizeof(int));
	int res_beg = 0, res_end = -1, candidate_beg = 0, candidate_end = -1;

	for(int i = 0; s[i]; i++)
	{
		char ch = s[i];
		if (occurences_count[index_from_char(ch)] == 0)
		{
			candidate_end ++;
			occurences_index[index_from_char(ch)] = i;
			occurences_count[index_from_char(ch)] ++;
			continue;
		}
		if (candidate_end - candidate_beg > res_end - res_beg)
		{
			res_end = candidate_end;
			res_beg = candidate_beg;
		}
		/* ch is a duplicate.... see how far back in the string ch occurs*/
		int prev_ch_index = occurences_index[index_from_char(ch)];
		for (int j = candidate_beg; j <= prev_ch_index; j++)
		{
			char wipe_char = s[j];
			occurences_count[index_from_char(wipe_char)] = 0;
			occurences_index[index_from_char(wipe_char)] = 0;
		}
		candidate_beg = prev_ch_index + 1;
		candidate_end = i;
		occurences_count[index_from_char(ch)] = 1;
		occurences_index[index_from_char(ch)] = i;
	}
	if (candidate_end - candidate_beg > res_end-res_beg)
	{
		res_beg = candidate_beg;
		res_end = candidate_end;
	}
	return res_end-res_beg + 1;
}




int main()
{
	printf("longest length for string abcabcbb is %d.\n", lengthOfLongestSubstring("abcabcbb"));

	printf("longest length for string bbbbb is %d.\n", lengthOfLongestSubstring("bbbbb"));
	printf("longest length for string pwwkew is %d.\n", lengthOfLongestSubstring("pwwkew"));

	return 0;
}
