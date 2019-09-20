/*
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
 * A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
 * Example: Input: "23" Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * Note: Although the above answer is in lexicographical order, your answer could be in any order you want.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

char digits_0[] = 	{' ',' ',' '};		/*dummy, makes indexing easier */
char digits_1[] = 	{' ',' ',' '};		/*dummy, makes indexing easier */
char digits_2[] = 	{'a','b','c'};
char digits_3[] = 	{'d','e','f'};
char digits_4[] = 	{'g','h','i'};
char digits_5[] = 	{'j','k','l'};
char digits_6[] = 	{'m','n','o'};
char digits_7[] = 	{'p','q','r','s'};
char digits_8[] = 	{'t','u','v'};
char digits_9[] = 	{'w','x','y','z'};

char * digits_tbl[] = {	digits_0, digits_1, digits_2, digits_3, digits_4, digits_5, digits_6, digits_7, digits_8, digits_9 };

int calculate_length_and_validate_digits(char * digits)
{
	int res = 1;
	for (;*digits;digits++)
	{
		if (*digits == '0' || *digits == '1' || *digits == '*' || *digits == '#') return 0;
		res = res * ((*digits == '7' || *digits == '9') ? 4 : 3);
	}
	return res;
}

void populate_combinations_recursive(char * digits, int digit_index, char ** res, int * res_index, char * working_buffer)
{
	char ch = digits[digit_index];
	/* base case */
	if (!ch)
	{
		memcpy(res[*res_index] /*dest*/, working_buffer /*src*/, sizeof(char)*(digit_index + 1));
		*res_index = *res_index + 1;
		return;
	}
	int letter_count = ( ch == '7' || ch == '9' ) ? 4 : 3;
	for (int i = 0; i < letter_count; i ++)
	{
		char letter = digits_tbl[(int) (ch-'0')][i];
		working_buffer[digit_index] = letter;
		populate_combinations_recursive(digits, digit_index + 1, res, res_index, working_buffer);
	}
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char * digits, int* returnSize)
{
	if (!digits || !(*digits)
	{
		*returnSize = 0;
		return NULL;
	}
	*returnSize = calculate_length_and_validate_digits(digits);
	if (!*returnSize) return NULL;

	int digits_len = strlen(digits);

	char * working_buffer = (char*) malloc(sizeof(char)*(digits_len+1));
	working_buffer[digits_len] = '\0';

	char ** res = (char **) malloc(sizeof(char*) * (*returnSize));
	for (int i = 0; i < *returnSize; i ++) res[i] = (char*) malloc(sizeof(char*) * (digits_len+1));
	int res_index = 0;

	populate_combinations_recursive(digits, 0, res, &res_index, working_buffer);
	return res;
}


void print_strings(char ** strings, int strings_sz)
{
	if (!strings || !strings_sz) return;
	for (int i = 0; i < strings_sz; i ++)
	{
		printf("\"%s\"\n", strings[i]);
	}
}

int main()
{
	char ** res;
	int res_sz;
	res = letterCombinations("23", &res_sz);
	print_strings(res, res_sz);
	return 0;
}

