/*
 *
 * https://leetcode.com/problems/reverse-words-in-a-string/
 * Given an input string, reverse the string word by word.
 * Example 1:  Input: "the sky is blue" Output: "blue is sky the"
 * Example 2: Input: "  hello world!  " Output: "world! hello"
 * Explanation: Your reversed string should not contain leading or trailing spaces.
 * Example 3: Input: "a good   example" Output: "example good a"
 * Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
 * Note:
 * A word is defined as a sequence of non-space characters.
 * Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
 * You need to reduce multiple spaces between two words to a single space in the reversed string.
 * Follow up: For C programmers, try to solve it in-place in O(1) extra space.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void reverse_string(char *s, int s_sz)
{
	char * beg = s, *end = s + s_sz - 1;
	while (beg < end)
	{
		char ch = *beg;
		*beg = *end;
		*end = ch;
		beg++;
		end--;
	}
}

void copy_to_first_two_white_spaces(char ** copy_to, char ** copy_from)
{
	/* should assert that *copy_to == ' ' and *copy_from != ' ' */
	bool encountered_first_white_space = false;
	while (**copy_from)
	{
		if (**copy_from == ' ')
		{
			if (encountered_first_white_space) break;
			encountered_first_white_space = true;
		}
		else
		{
			encountered_first_white_space = false;
		}
		**copy_to = **copy_from;
		*copy_to = *copy_to + 1;
		**copy_from = ' ';
		*copy_from = *copy_from + 1;
	}
}

void remove_un_needed_spaces(char *s, int s_sz)
{
	/* some base cases */
	if (*s == ' '&& *(s+1) == '\0') {*s = '\0'; return;}
	if (*(s+1) == ' '&& *(s+2) == '\0'){*(s+1) = '\0'; return;}

	/* cleanup the trailing white spaces */
	for (int i = s_sz - 1; i >= 0 && s[i] == ' '; i --)
	{
		s[i] = '\0';
	}

	/* clean up the leading white spaces */
	char * copy_to = s, *copy_from = s;
	if (*s== ' ')
	{
		while (*copy_from == ' ') copy_from ++;
		if (!*copy_from)
		{
			/* this string has only white spaces */
			*s = '\0';
			return;
		}
		copy_to_first_two_white_spaces(&copy_to, &copy_from);
	}
	else
	{
		/* find the first two white spaces in a row */
		while (*copy_to && *(copy_to+1) && !(*copy_to == ' ' && *(copy_to+1) ==  ' ')) copy_to ++;
		if (!*copy_to) return;
		if (!*(copy_to+1))
		{
			if (*copy_to == ' ') *copy_to = '\0';
			return;
		}
		copy_to ++;
		copy_from = copy_to + 1;
		while (*copy_from == ' ') copy_from ++;
		if (!*copy_from)
		{
			/* there are only white spaces after the first two white spaces */
			if (*copy_to == ' ') *copy_to = '\0';
			return;
		}
	}
	while (*copy_from && *copy_to)
	{
		while (*copy_from == ' ') copy_from ++;
		if (!*copy_from)
		{
			/* there are only white spaces after the first two white spaces */
			if (*copy_to == ' ') *copy_to = '\0';
			return;
		}
		copy_to_first_two_white_spaces(&copy_to, &copy_from);
		while (*copy_from == ' ') copy_from ++;
		if (!*copy_from)
		{
			/* there are only white spaces after the first two white spaces */
			if (*copy_to == ' ') *copy_to = '\0';
			return;
		}
	}
	if (*copy_to == ' ') *copy_to = '\0';
}

char * reverseWords(char * s)
{
	if (!s || !(*s)) return s;
	int s_len = strlen(s);
	remove_un_needed_spaces(s, s_len);
	if (!(*s)) return "";
	s_len = strlen(s);
	reverse_string(s, s_len);
	char * word_beg = s, *word_end = word_beg;
	while (word_beg < s + s_len)
	{
		while (*word_end && *word_end != ' ') word_end ++;
		reverse_string(word_beg, word_end-word_beg);
		word_beg = word_end + 1;
		word_end = word_beg;
	}

	return s;
}



int main()
{
	printf("testing the clean-up function.\n");
	char s[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	memcpy(s /*dest*/, "abc" /*src*/, strlen("abc"));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, " abc" /*src*/, strlen(" abc"));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "  abc " /*src*/, strlen("  abc "));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "  abc dfe  ghi" /*src*/, strlen("  abc dfe  ghi"));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "  abc dfe  ghi " /*src*/, strlen("  abc dfe  ghi "));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "  abc dfe f ghi   " /*src*/, strlen("  abc dfe f ghi   "));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "  abc dfe   ghi   " /*src*/, strlen("  abc dfe   ghi   "));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "  abc dfe   ghi  j" /*src*/, strlen("  abc dfe   ghi  j"));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "  abc dfe   ghi   j    k" /*src*/, strlen("  abc dfe   ghi   j    k"));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	memcpy(s, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 45);
	memcpy(s /*dest*/, "abc dfe   ghi   j    k       l   mn op   " /*src*/, strlen("abc dfe   ghi   j    k       l   mn op   "));
	printf("input string \"%s\"", s); remove_un_needed_spaces(s, strlen(s)); printf(", cleanup output is \"%s\"\n", s);
	

	char reverse[] = "ats";
	char * reversed = reverseWords(reverse);
	printf("reversed words \"%s\"\n", reversed);
	return 0;
}
