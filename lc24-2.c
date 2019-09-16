/*
 *
 * https://leetcode.com/accounts/login/?next=/problems/longest-substring-with-at-most-k-distinct-characters/
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define alphabet_sz (26)
#define index_from_char(ch) ((int) (ch-'a'))

int lengthOfLongestSubstringKDistinct(char * s, int k)
{
	/* some base cases */
	if (!k) return 0;
	if (!s || !(*s)) return 0;
	if (!(*(s+1))) return 1;
	int letters_found_count[alphabet_sz];
	memset(letters_found_count, 0, sizeof(int)*alphabet_sz);
	bool letters_found[alphabet_sz];
	memset(letters_found, 0, sizeof(bool)*alphabet_sz);
	int curr_window_beg = 0, curr_window_end = 0;
	int res_beg = 0, res_end = 0;
	int diff_letters_count = 0;
	for (int i = 0; s[i]; i++)
	{
		char ch = s[i];
		int ch_index = index_from_char(ch);
		letters_found_count[ch_index] = letters_found_count[ch_index] + 1;
		letters_found[ch_index] = true;

		/* if we saw this character in the sliding window keep going */
		if (letters_found_count[ch_index] > 1)
		{
			curr_window_end = i;
			continue;
		}

		diff_letters_count ++;
		/* still under the k-limit so keep going */
		if (diff_letters_count <= k)
		{
			curr_window_end = i;
			continue;
		}
		if (curr_window_end - curr_window_beg > res_end - res_beg)
		{
			res_end = curr_window_end;
			res_beg = curr_window_beg;
		}
		/* have to move the right post of the sliding window to the left until there are only k distinct characters in the window */
		for (;;curr_window_beg++)
		{
			char beg_ch = s[curr_window_beg];
			int beg_ch_index = index_from_char(beg_ch);
			letters_found_count[beg_ch_index] = letters_found_count[beg_ch_index] - 1;
			if (letters_found_count[beg_ch_index]) continue;
			letters_found[beg_ch_index] = false;
			curr_window_beg ++;
			diff_letters_count --;
			break;
		}
	}
	if (curr_window_end - curr_window_beg > res_end - res_beg)
	{
		res_end = curr_window_end;
		res_beg = curr_window_beg;
	}
	return res_end - res_beg + 1;
}

int main()
{
	int res = lengthOfLongestSubstringKDistinct("eceba", 2);
	printf("%d.\n", res);
	res = lengthOfLongestSubstringKDistinct("aa", 1);
	printf("%d.\n", res);
	res = lengthOfLongestSubstringKDistinct("ab", 1);
	printf("%d.\n", res);
	res = lengthOfLongestSubstringKDistinct("a", 2);
	printf("%d.\n", res);
	res = lengthOfLongestSubstringKDistinct("ecebaaabc", 3);
	printf("%d.\n", res);
	return 0;
}
