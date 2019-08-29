/*
 *
 * https://leetcode.com/problems/word-search/
 * The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.
 * Example:
 * board =
 * [
 *   ['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']
 * ]
 * Given word = "ABCCED", return true.
 * Given word = "SEE", return true.
 * Given word = "ABCB", return false.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool recursive_exist(char **board, int width, int height, char * word, int x, int y)
{
	if (!(*word)) return true;	/* got to the end of the string */
	if (x >= width || x < 0 || y >= height || y < 0) return false;
	if (board[y][x] == *word)
	{
		char c = *word;
		board[y][x] = '\0';
		bool res = recursive_exist(board, width, height, word+1, x + 1, y);
		res = res || recursive_exist(board, width, height, word+1, x - 1, y);
		res = res || recursive_exist(board, width, height, word+1, x, y + 1);
		res = res || recursive_exist(board, width, height, word+1, x, y - 1);
		board[y][x] = c;
		return res;
	}
	else
	{
		return false;
	}
}

bool exist(char** board, int boardSize, int* boardColSize, char * word)
{
	if (!word || !(*word)) return true;	/* empty string fits any board, even the empty one */
	if (!board || !boardSize || !boardColSize || !(*boardColSize)) return false;
	int height = boardSize, width = * boardColSize;
	for (int i = 0; i < width; i ++)
	{
		for (int j = 0; j < height; j++)
		{
			if (recursive_exist(board, width, height, word, i, j)) return true;
		}
	}
	return false;
}

int main()
{
       char r1[]={"ABCE"};
       char r2[]={"SFCS"};
       char r3[]={"ADEE"};
       char * board[] = {r1,r2,r3};
	   int boardColSize = 4;
	   bool res = exist(board, 3, &boardColSize, "ABCCED");
	   printf("result is %s, expected TRUE.\n", (res ? "TRUE" : "FALSE"));
	   res = exist(board, 3, &boardColSize, "SEE");
	   printf("result is %s, expected TRUE.\n", (res ? "TRUE" : "FALSE"));
	   res = exist(board, 3, &boardColSize, "ABCB");
	   printf("result is %s, expected FALSE.\n", (res ? "TRUE" : "FALSE"));
	   return 0;
}
