/*
 *
 * https://leetcode.com/problems/minimum-window-substring/
 * Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
 * Example: Input: S = "ADOBECODEBANC", T = "ABC"
 * Output: "BANC"
 * Note:
 * If there is no such window in S that covers all characters in T, return the empty string "".
 * If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define index_from_char(c) ((int) (c-'\0'))

typedef struct list_t
{
	struct list_t * next;
	char ch;
	int index;
} list;

typedef struct window_t
{
	int * tgt_occurences;
	int occurences[256];
	list * l, *tail;
	bool contains_result;
} window;

bool check_occurences(int * tgt, int * check_array, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		if (tgt[i] > check_array[i]) return false;
	}
	return true;
}

void add_char_to_window(window * w, char ch, int index)
{
	list * new_node = (list*) malloc(sizeof(list));
	memset(new_node, 0, sizeof(list));
	new_node->ch = ch;
	new_node->index = index;
	if (w->l)
	{
		w->tail->next = new_node;
	}
	else
	{
		w->l = new_node;
	}
	w->tail = new_node;
	w->occurences[index_from_char(ch)] = w->occurences[index_from_char(ch)] + 1;
	w->contains_result = w->contains_result || check_occurences(w->tgt_occurences, w->occurences, 256);
	if (!w->contains_result) return;
	while (w->occurences[(index_from_char(w->l->ch))] > w->tgt_occurences[(index_from_char(w->l->ch))])
	{
		w->occurences[index_from_char(w->l->ch)] = w->occurences[index_from_char(w->l->ch)] - 1;
		list * del_node = w->l;
		w->l = w->l->next;
		free(del_node);
	}
}

void free_window(window * w)
{
	list * h = w->l;
	while (h)
	{
		list *next = h->next;
		free(h);
		h = next;
	}
}

char * fast_search_one_char_tgt(char *s, char tgt)
{
	bool found_tgt = false;
	for (;*s;s++)
	{
		if (*s == tgt)
		{
			found_tgt = true;
			break;
		}
	}
	if (found_tgt)
	{
		char * res = (char *) malloc(2 * sizeof(char));
		res[0] = tgt;
		res[1] = '\0';
		return res;
	}
	else
	{
		return "";
	}
}

char * minWindow_duplicates(char *s, char *t)
{
	if (!s || !t || !*s || !*t) return "";
	int tgt_occurences[256];
	memset(tgt_occurences, 0, 256 * sizeof(int));

	int tgt_letters_count = 0;

	for (int i = 0;t[i]; i++)
	{
		tgt_occurences[index_from_char(t[i])] ++;
		tgt_letters_count ++;
	}
	
	if (tgt_letters_count == 1) return fast_search_one_char_tgt(s, *t);

	window w;
	memset(&w, 0, sizeof(window));
	w.tgt_occurences = tgt_occurences;
	int res_beg = 0, res_end = INT_MAX;
	for (int i = 0; s[i]; i ++)
	{
		if (!tgt_occurences[index_from_char(s[i])]) continue;
		add_char_to_window(&w, s[i], i);
		if (w.contains_result)
		{
			int max = w.tail->index;
			int min = w.l->index;
			if (max-min < res_end - res_beg)
			{
				res_end = max;
				res_beg = min;
			}
		}
	}
	char * res;
	if (w.contains_result)
	{
		res = (char*) malloc((res_end-res_beg + 2) * sizeof(char));
		memcpy(res /*dest*/, s+res_beg /*src*/, (res_end-res_beg+1)*sizeof(char));
		res[res_end-res_beg+1] = '\0';
	}
	else
	{
		res = "";
	}
	free_window(&w);
	return res;
}

void check_arr(int * occurences, int * min_index, int *max_index)
{
	*min_index = INT_MAX;
	*max_index = INT_MIN;
	for (int i = 0; i < 256; i ++)
	{
		if (occurences[i] == 0) continue;
		if (occurences[i] > *max_index) *max_index = occurences[i];
		if (occurences[i] < *min_index) *min_index = occurences[i];
	}
}

char * minWindow(char * s, char * t)
{
	if (!s || !t) return "";

	int alphabet[256];
	int occurences[256];		/* index of occurences of letter  in the input string */
	memset(alphabet, 0, 256 * sizeof(int));
	memset(occurences,0, 256 * sizeof(int));
	int candidate_min =0, candidate_max = INT_MAX;
	int diff_letters_found = 0;			/* number of different letters in target found in the input string */
	int diff_tgt_letters = 0;
	for(;*t;t++)
	{
		if (alphabet[index_from_char(*t)] ==0) diff_tgt_letters ++;
		alphabet[index_from_char(*t)] ++;
	}

	for (int i = 0; s[i]; i++)
	{
		char ch = s[i];
		if (!alphabet[index_from_char(ch)]) continue;
		if (!occurences[index_from_char(ch)])
		{
			diff_letters_found ++;
			occurences[index_from_char(ch)] = i+1;
		}
		if (diff_letters_found == diff_tgt_letters)
		{
			int new_min, new_max;
			occurences[index_from_char(ch)] = i+1;
			check_arr(occurences, &new_min, &new_max);
			if (new_max - new_min < candidate_max - candidate_min)
			{
				candidate_min = new_min;
				candidate_max = new_max;
			}
		}
	}
	if (diff_letters_found < diff_tgt_letters) return "";
	char * res = (char *) malloc((candidate_max-candidate_min + 2)*sizeof(char));
	memcpy(res /*dest*/, s+candidate_min-1 /*src*/, (candidate_max-candidate_min+1)*sizeof(char));
	res[candidate_max - candidate_min + 1] = '\0';
	return res;
}


int main()
{
	char * res = minWindow("ADOBECODEBANC", "ABC");
	printf("result is: %s\n",res);
	free(res);
	res = minWindow_duplicates("ADOBECODEBANC", "ABC");
	printf("result with duplicates: %s\n", res);
	free(res);
	res = minWindow_duplicates("ADOBECODEBANC", "AAA");
	printf("result with duplicates: %s\n", res);
	res = minWindow_duplicates("ab", "a");
	printf("result with duplicates: %s\n", res);
	free(res);
	res = minWindow_duplicates("aa", "aa");
	printf("result with duplicates: %s\n", res);
	free(res);
	res = minWindow_duplicates("ab", "ba");
	printf("result with duplicates: %s\n", res);
	free(res);
	res = minWindow_duplicates("ab", "ab");
	printf("result with duplicates: %s\n", res);
	free(res);
	res = minWindow_duplicates("abc", "ab");
	printf("result with duplicates: %s\n", res);
	free(res);
	res = minWindow_duplicates("cabefgecdaecf", "cae");
	printf("result with duplicates: %s\n", res);
	free(res);
	return 0;
}

