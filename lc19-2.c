/*
 *
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 * You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
 * Example 1: Input: s = "barfoothefoobarman", words = ["foo","bar"] Output: [0,9]
 * Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
 * The output order does not matter, returning [9,0] is fine too.
 * Example 2: Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"] Output: []
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define alphabet_sz (26)
#define index_from_char(ch) ((int) (ch-'a'))

typedef struct trie_end_t
{
	int word_used;
} trie_end;


typedef struct trie_t
{
	struct trie_t ** children;
	trie_end * end;
} trie;

void add_word_to_trie(trie * t, char * word, int index_in_word_list)
{
	int word_size = 0;
	for (;*word;word++)
	{
		if (!t->children)
		{
			t->children = (trie **) malloc(sizeof(trie*) * alphabet_sz);
			memset(t->children, 0, sizeof(trie*) * alphabet_sz);
		}
		if (!t->children[index_from_char(*word)])
		{
			trie * next_level = (trie *) malloc(sizeof(trie));
			memset(next_level, 0, sizeof(trie));
			t->children[index_from_char(*word)] = next_level;
		}
		t = t->children[index_from_char(*word)];
		word_size ++;
	}
	if (!t->end)
	{
		t->end = (trie_end*) malloc(sizeof(trie_end));
		t->end->word_used = 1;
	}
	else
	{
		t->end->word_used = t->end->word_used + 1;
	}
}

void free_trie(trie * t)
{
	if (!t) return;
	if (t->children)
	{
		for (int i = 0; i < alphabet_sz; i ++)
		{
			free_trie(t->children[i]);
		}
	}
	if (t->end) free(t->end);
	free(t);
}

bool match_concatenation(char * s, trie * t, int words_used_so_far, int wordsSize)
{
	if (words_used_so_far == wordsSize) return true;
	if (!(*s)) return false;

	trie * current = t;
	while (current && current->children && current->children[index_from_char(*s)])
	{
		trie * next = current->children[index_from_char(*s)];
		if (next->end)
		{
			if (next->end->word_used)
			{
				int words_used = next->end->word_used;
				next->end->word_used = next->end->word_used - 1;
				bool res = match_concatenation(s+1,t, words_used_so_far + 1, wordsSize);
				next->end->word_used = words_used;
				if (res) return true;
			}
		}
		current = next;
		s++;
	}
	return false;
}

void checksums(char * s, int s_len, int * c1, int * c2, int * c3)
{
	*c1 = 0; *c2 = 0; *c3 = 0;
	for (int i = 0; i < s_len; i ++)
	{
		int ch = index_from_char(s[i]);
		int ch_squared = ch * ch;
		int ch_cubed = ch_squared * ch;
		*c1 += ch;
		*c2 += ch_squared;
		*c3 += ch_cubed;
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char * s, char ** words, int wordsSize, int* returnSize)
{
	/* some base cases */
	if (!s || !(*s) || !words || !wordsSize)
	{
		*returnSize = 0;
		return NULL;
	}

	*returnSize = 0;

	int s_len = strlen(s);
	int words_total_len = 0;
	trie * t = (trie *) malloc(sizeof(trie));
	memset(t, 0, sizeof(trie));
	int words_c1 = 0, words_c2 = 0, words_c3 = 0;
	for (int i = 0; i < wordsSize; i ++)
	{
		add_word_to_trie(t, words[i], i);
		int word_len = strlen(words[i]);
		words_total_len += word_len;
		int c1, c2, c3;
		checksums(words[i], word_len, &c1, &c2, &c3);
		words_c1 += c1; words_c2 += c2; words_c3 += c3;
	}
	int * res = NULL;
	int res_sz = 0;
	int s_c1, s_c2, s_c3;
	checksums(s, words_total_len, &s_c1, &s_c2, &s_c3);
	for (int i = 0; i <= s_len - words_total_len; i ++)
	{
		if (i > 0)
		{
			int old_ch = index_from_char(s[i-1]); int old_ch_squared = old_ch * old_ch; int old_ch_cubed = old_ch_squared * old_ch;
			s_c1 -= old_ch; s_c2 -= old_ch_squared; s_c3 -= old_ch_cubed;
			int new_ch = index_from_char(s[i + words_total_len-1]); int new_ch_squared = new_ch * new_ch; int new_ch_cubed = new_ch_squared * new_ch;
			s_c1 += new_ch; s_c2 += new_ch_squared; s_c3 += new_ch_cubed;
		}
		if (s_c1 == words_c1 && s_c2 == words_c2 && s_c3 == words_c3 && match_concatenation(s+i, t, 0, wordsSize))
		{
			*returnSize = *returnSize +1;
			if (*returnSize > res_sz)
			{
				res_sz += 5;
				res = realloc(res, res_sz * sizeof(int));
			}
			res[(*returnSize)-1] = i;
		}
	}
	free_trie(t);
	return res;
}

void print_int_array(int * arr, int arr_sz)
{
	if (!arr || !arr_sz) return;
	printf("[%d", arr[0]);
	for (int i = 1; i < arr_sz; i++)
	{
		printf(",%d", arr[i]);
	}
	printf("]\n");
}

int main()
{
	int res_sz = 0;
	char * words[] = {"word", "good", "best", "word"};
	int * res = findSubstring("wordgoodgoodgoodbestword", words, 2, &res_sz);
	print_int_array(res, res_sz);

	res = findSubstring("wordgoodgoodgoodbestword", words, 3, &res_sz);
	print_int_array(res, res_sz);

	res = findSubstring("wordgoodgoodgoodbestword", words, 4, &res_sz);
	print_int_array(res, res_sz);

	char * words2[] = {"word", "good", "best", "good"};
	res = findSubstring("wordgoodgoodgoodbestword", words2, 4, &res_sz);
	print_int_array(res, res_sz);

	char * words3[] = {"foo", "bar"};
	res = findSubstring("barfoothefoobarman", words3, 2, &res_sz);
	print_int_array(res, res_sz);
	
	return 0;
}
