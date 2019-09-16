/*
 *
 * https://leetcode.com/problems/text-justification/
 * Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
 * You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
 * Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
 * For the last line of text, it should be left justified and no extra space is inserted between words.
 * Note: A word is defined as a character sequence consisting of non-space characters only. Each word's length is guaranteed to be greater than 0 and not exceed maxWidth. The input array words contains at least one word.
 * Example 1: Input: words = ["This", "is", "an", "example", "of", "text", "justification."] maxWidth = 16
 * Output:
 * [
 *    "This    is    an",
 *    "example  of text",
 *    "justification.  "
 * ]
 * Example 2: Input: words = ["What","must","be","acknowledgment","shall","be"] maxWidth = 16
 * Output:
 * [
 *   "What   must   be",
 *   "acknowledgment  ",
 *   "shall be        "
 * ]
 * Explanation: Note that the last line is "shall be    " instead of "shall     be", because the last line must be left-justified instead of fully-justified. Note that the second line is also left-justified becase it contains only one word.
 * Example 3: Input:  words = ["Science","is","what","we","understand","well","enough","to","explain", "to","a","computer.","Art","is","everything","else","we","do"] maxWidth = 20
 * Output:
 * [
 *   "Science  is  what we",
 *   "understand      well",
 *   "enough to explain to",
 *   "a  computer.  Art is",
 *   "everything  else  we",
 *   "do                  "
 * ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

char * build_last_line(char ** words, int start, int end, int maxWidth, int * words_lengths)
{
	char * res = (char *) malloc(sizeof(char) * (maxWidth+1));
	int res_index = 0;
	memcpy(res + res_index /*dest*/, words[start] /*src*/, words_lengths[start]);
	res_index += words_lengths[start];
	for (int i = start + 1; i <= end; i ++)
	{
		res[res_index] = ' ';
		res_index ++;
		memcpy(res + res_index /*dest*/, words[i] /*src*/, words_lengths[i]);
		res_index += words_lengths[i];
	}

	for (int i = res_index; i < maxWidth; i ++)
	{
		res[i] = ' ';
	}
	res[maxWidth] = '\0';
	return res;
}

char * build_one_word_line(char * word, int word_len, int maxWidth)
{
	char * res = (char *) malloc(sizeof(char) * (maxWidth+1));
	memcpy(res /*dest*/, word /*src*/, word_len);
	for (int i = word_len; i < maxWidth; i ++)
	{
		res[i] = ' ';
	}
	res[maxWidth] = '\0';

	return res;
}

void copy_white_spaces(char * buff, int white_spaces_count)
{
	for (int i = 0; i < white_spaces_count; i ++)
	{
		buff[i] = ' ';
	}
}

char * build_line(char ** words, int start, int end, int cumm_len, int maxWidth, int * words_lengths)
{
	int total_white_spaces_count = maxWidth - cumm_len;
	int copy_white_spaces_padding = total_white_spaces_count / (end-start);
	int number_larger_white_spaces = total_white_spaces_count - copy_white_spaces_padding * (end-start);
	int larger_white_spaces_copied = 0;
	int res_index = 0;
	char * res = (char *) malloc(sizeof(char) * (maxWidth + 1));
	memcpy(res + res_index /*dest*/, words[start], words_lengths[start]);
	res_index += words_lengths[start];
	for (int i = start+1; i <= end; i ++)
	{
		int white_spaces_to_copy = copy_white_spaces_padding;
		if (larger_white_spaces_copied < number_larger_white_spaces)
		{
			white_spaces_to_copy ++;
			larger_white_spaces_copied ++;
		}
		copy_white_spaces(res + res_index, white_spaces_to_copy);
		res_index += white_spaces_to_copy;
		memcpy(res + res_index /*dest*/, words[i], words_lengths[i]);
		res_index += words_lengths[i];
	}
	res[maxWidth] = '\0';
	return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fullJustify(char ** words, int wordsSize, int maxWidth, int* returnSize)
{
	*returnSize = 0;
	int * words_lengths = (int *) malloc(sizeof(int) * wordsSize);
	for (int i = 0; i < wordsSize; i ++)
	{
		words_lengths[i] = strlen(words[i]);
	}

	char ** res = (char **)malloc(sizeof(char *) * wordsSize);

	for (int i = 0; i < wordsSize; )
	{
		char * new_line;
		int start = i, end = i;
		int cumm_len = words_lengths[end];
		while (end + 1 < wordsSize && cumm_len + 1 + words_lengths[end+1] <= maxWidth)
		{
			end ++;
			cumm_len += words_lengths[end] + 1;
		}
		if (end == wordsSize-1)
		{
			new_line = build_last_line(words, start, end, maxWidth, words_lengths);
		}
		else if (end == start)
		{
			new_line = build_one_word_line(words[start], words_lengths[start], maxWidth);
		}
		else
		{
			cumm_len -= end - start;
			new_line = build_line(words, start, end, cumm_len, maxWidth, words_lengths);
		}
		res[*returnSize] = new_line;
		*returnSize = *returnSize + 1;
		i = end + 1;
	}

	free(words_lengths);
	return res;
}


void print_lines(char ** lines, int lines_count)
{
	if (!lines || !lines_count) return;
	printf("***********************************\n");
	for (int i = 0; i < lines_count; i ++)
	{
		printf("\"%s\"\n", lines[i]);
	}
	printf("***********************************\n");
}

int main()
{
	char ** res;
	int return_size;
	char * words[] = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
	res = fullJustify(words, 18, 20, &return_size);
	print_lines(res, return_size);
	char * words2[]={"This", "is", "an", "example", "of", "text", "justification."};
	res = fullJustify(words2, 7, 16, & return_size);
	print_lines(res,return_size);
	char * words3[] = {"What","must","be","acknowledgment","shall","be"};
	res = fullJustify(words3, 6, 16, &return_size);
	print_lines(res, return_size);
	return 0;
}
