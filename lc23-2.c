/*
 *
 * https://leetcode.com/problems/delete-operation-for-two-strings/
 * Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.
 * Example 1: Input: "sea", "eat" Output: 2
 * Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
 * Note:  The length of given words won't exceed 500. Characters in given words can only be lower-case letters.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int string_contains_char(char * s, char c)
{
	for (;*s;s++)
	{
		if (*s==c) return 1;
	}
	return 0;
}

int string_contains_2chars(char *s, char a, char b)
{
	int found_a = 0, found_b = 0;
	for (;*s;s++)
	{
		if (*s==a && !found_a)
		{
			found_a = 1;
			continue;
		}
		if (*s==b)
		{
			if (found_a) return 2;
			found_b = 1;
		}
	}
	return found_a > found_b ? found_a : found_b;
}

int max_sub_sequence_len_recursive(char * w1, char * w2, int w1_index, int w2_index, int w1_len, int w2_len, int * cache)
{
	if (w1_index >= w1_len || w2_index > w2_len) return 0;
	/* check the cache */
	if (cache[w1_len * w2_index + w1_index] != -1) return cache[w1_len * w2_index + w1_index];

	/* base cases: last char in either string */
	if (w1_index == w1_len-1)
	{
		int w2_contains_ch = string_contains_char(w2+w2_index, w1[w1_index]);
		cache[w1_len * w2_index + w1_index] = w2_contains_ch;
		return w2_contains_ch;
	}

	if (w2_index == w2_len-1)
	{
		int w1_contains_ch = string_contains_char(w1+w1_index, w2[w2_index]);
		cache[w1_len * w2_index + w1_index] = w1_contains_ch;
		return w1_contains_ch;
	}

	/* base cases: last two chars in either string */
	if (w1_index == w1_len-2)
	{
		int w2_contains_chars = string_contains_2chars(w2+w2_index, w1[w1_index], w1[w1_index+1]);
		cache[w1_len * w2_index + w1_index] = w2_contains_chars;
		return w2_contains_chars;
	}

	if (w2_index == w2_len-2)
	{
		int w1_contains_chars = string_contains_2chars(w1+w1_index, w2[w2_index], w2[w2_index+1]);
		cache[w1_len * w2_index + w1_index] = w1_contains_chars;
		return w1_contains_chars;
	}

	int res = max_sub_sequence_len_recursive(w1, w2, w1_index + 1, w2_index + 1, w1_len, w2_len, cache);
	if(w1[w1_index] == w2[w2_index])
	{
		res ++;
	}
	int tmp = max_sub_sequence_len_recursive(w1, w2, w1_index + 1, w2_index, w1_len, w2_len, cache);
	res = tmp > res ? tmp : res;
	tmp = max_sub_sequence_len_recursive(w1, w2, w1_index, w2_index + 1, w1_len, w2_len, cache);
	res = tmp > res ? tmp : res;
	cache[w1_len * w2_index + w1_index] = res;
	return res;
}

int minDistance(char * word1, char * word2)
{
	/* some base cases */
	if (!word1 && !word2) return 0;
	if (!word1 || !*word1) return strlen(word2);
	if (!word2 || !*word2) return strlen(word1);

	int w1_len = strlen(word1);
	int w2_len = strlen(word2);
	int * cache = (int *) malloc(w1_len * w2_len * sizeof(int));
	for (int i = 0; i < w1_len * w2_len; i++)
	{
		cache[i] = -1;
	}

	int max_len = max_sub_sequence_len_recursive(word1, word2, 0, 0, w1_len, w2_len, cache);
	int res = strlen(word1) - max_len + strlen(word2) - max_len;

	free (cache);
	return res;
}


int main()
{
	//char a[] = "ccb";
	//char b[] = "bab";

	//char a[] = "abcbccb";
	//char b[] = "aabcabab";


	//char a[] = "dinitrophenylhydrazine";
	//char b[] = "acetylphenylhydrazine";

	//char a[] = "ntzte";
	//char b[] = "jowtt";

	char a[] = "ntzte";
	char b[] = "tt";


	//char a[] = "ccbab";
	//char b[] = "ab";
	//char a[] = "ccb";
	//char b[] = "ab";
	//char a[] = "ccb";
	//char b[] = "abcb";
	//char a[] = "abcdxabcde";
	//char b[] = "abcdeabcdx";
	//char a[] = "abcdx";
	//char b[] = "abcde";
	printf("min distance for \"%s\" and \"%s\" is %d.\n", a, b, minDistance(a,b));
	return 0;
}
