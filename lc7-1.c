/*
 *
 * https://leetcode.com/problems/number-of-islands/
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 * Example 1:
 * Input:
 * 11110
 * 11010
 * 11000
 * 00000
 * Output: 1
 * Example 2:
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void fill_island(char ** grid, int width, int height, int x, int y)
{
	grid[x][y] = 'Y';
	/* flip the neighbor to the right */
	if (y < width-1 && grid[x][y + 1] == '1') fill_island(grid, width, height, x, y+1);
	/* flip the neighbor to the left */
	if (y>0 && grid[x][y-1] == '1') fill_island(grid, width, height, x, y-1);
	/* flip the neighbor above */
	if (x>0 && grid[(x-1)][y] == '1') fill_island(grid, width, height, x - 1, y);
	/* flip the neighbor below */
	if (x < height-1 && grid[(x+1)][y] == '1') fill_island(grid, width, height, x +1,y);
}

int numIslands(char** grid, int gridSize, int* gridColSize)
{
	if (!grid || !gridSize || !gridColSize || !*gridColSize) return 0;
	int width = *gridColSize, height = gridSize;
	int res = 0;
	for (int i = 0; i < height; i ++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == '1')
			{
				res ++;
				fill_island(grid, width, height, i, j);
			}
		}
	}
	return res;
}



int main()
{
	char r1[]={"11000"};
	char r2[]={"11000"};
	char r3[]={"00100"};
	char r4[]={"00011"};
	char * grid[] = {r1,r2,r3,r4};
	int gridColSize = 5;
	int res = numIslands(grid,4, &gridColSize);
	printf("result is %d.\n", res);
	return 0;
}

