/*
 *
 * https://leetcode.com/problems/compare-version-numbers/
 * Compare two version numbers version1 and version2.
 * If version1 > version2 return 1; if version1 < version2 return -1;otherwise return 0.
 * You may assume that the version strings are non-empty and contain only digits and the . character.
 * The . character does not represent a decimal point and is used to separate number sequences.
 * For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.
 * You may assume the default revision number for each level of a version number to be 0.
 * 		For example, version number 3.4 has a revision number of 3 and 4 for its first and second level revision number.
  * 	Its third and fourth level revision number are both 0.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int ver_atoi(char * s, char **out)
{
	int res = 0;
	while(*s && (*s != '.'))
	{
		res = res * 10 + (int)( (*s) - '0');
		s++;
	}
	*out = s;
	return res;
}

int compareVersion(char * version1, char * version2)
{
	while (*version1 && *version2)
	{
		int v1 = 0, v2 = 0;
		char *s1, *s2;
		v1 = ver_atoi(version1, &s1);
		v2 = ver_atoi(version2, &s2);
		if (v1 < v2) return -1;
		if (v1 > v2) return 1;
		version1 = s1;
		if (*version1=='.') version1++;
		version2 = s2;
		if (*version2=='.') version2++;
	}
	while (*version2)
	{
		if (*version2 >= '1' && *version2 <= '9') return -1;
		version2++;
	}
	while (*version1)
	{
		if (*version1 >= '1' && *version1 <= '9') return 1;
		version1++;
	}
	return 0;
}



int main()
{
	printf("results is %d. expected -1\n", compareVersion("0.1", "1.1"));
	printf("results is %d. expected 1\n", compareVersion("1.0.1", "1"));
	printf("results is %d. expected -1\n", compareVersion("7.5.2.4", "7.5.3"));
	printf("results is %d. expected 0\n", compareVersion("1.01", "1.001"));
	printf("results is %d. expected 0\n", compareVersion("1.0", "1.0.0"));
	return 0;
}
