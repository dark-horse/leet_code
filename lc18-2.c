/*
 *
 * https://leetcode.com/problems/edit-distance/
 * Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
 * You have the following 3 operations permitted on a word:
 * Insert a character
 * Delete a character
 * Replace a character
 * Example 1: Input: word1 = "horse", word2 = "ros" Output: 3
 * Explanation: 
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 * Example 2: Input: word1 = "intention", word2 = "execution" Output: 5
 * Explanation: 
 * intention -> inention (remove 't')
 * inention -> enention (replace 'i' with 'e')
 * enention -> exention (replace 'n' with 'x')
 * exention -> exection (replace 'n' with 'c')
 * exection -> execution (insert 'u')
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


int min_dist_recursive(char * w1, char * w2, int w1_len, int w2_len, int w1_index, int w2_index, int * cache)
{
	if (w1_index == w1_len)
	{
		return w2_len - w2_index;
	}
	if (w2_index == w2_len)
	{
		return w1_len - w1_index;
	}
	if (cache[w1_len * w2_index + w1_index]) return cache[w1_len * w2_index + w1_index];
	/* one way to edit is to recurse on the smaller strings */
	/* If the first characters are different the to change from one string into another we need one edit: replace a character */
	/* if the firt characters are the same, we don't need to do anything else */
	int res = min_dist_recursive(w1, w2, w1_len, w2_len, w1_index + 1, w2_index + 1, cache);
	if (w1[w1_index] != w2[w2_index]) res ++;
	/* another way to edit is to recurse on the first string only */
	/* then we need one more operation: delete the first character on the second string */
	int tmp = min_dist_recursive(w1, w2, w1_len, w2_len, w1_index + 1, w2_index, cache);
	tmp ++;
	res = res > tmp ? tmp: res;
	/* the last way to recurse is basically the reverse of the second way */
	tmp = min_dist_recursive(w1, w2, w1_len, w2_len, w1_index, w2_index+1, cache);
	tmp ++;
	res = res > tmp ? tmp: res;
	cache[w1_len * w2_index + w1_index] = res;
	return res;
}

int minDistance(char * word1, char * word2)
{
	if ((!word1 || !(*word1)) && (!word2 || !(*word2))) return 0;

	if (!word1 || !(*word1)) return strlen(word2);
	if (!word2 || !(*word2)) return strlen(word1);

	int w1_len = strlen(word1), w2_len = strlen(word2);
	int * cache = (int *) malloc(sizeof(int) * w1_len * w2_len);
	memset(cache, 0, sizeof(int) * w1_len * w2_len);
	int res = min_dist_recursive(word1, word2, w1_len, w2_len, 0, 0, cache);
	free(cache);
	return res;
}

int main()
{
	printf("edit distance for strings \"horse\" and \"rose\" is %d.\n", minDistance("horse", "rose"));
	printf("edit distance for strings \"horse\" and \"ros\" is %d.\n", minDistance("horse", "ros"));
	printf("edit distance for strings \"intention\" and \"execution\" is %d.\n", minDistance("intention", "execution"));
	return 0;
}
