/*
 *
 * https://leetcode.com/problems/spiral-matrix/
 * Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
 * Example 1: Input:
 * [
 *  [ 1, 2, 3 ],
 *  [ 4, 5, 6 ],
 *  [ 7, 8, 9 ]
 * ]
 * Output: [1,2,3,6,9,8,7,4,5]
 * Example 2: Input:
 * [
 *   [1, 2, 3, 4],
 *   [5, 6, 7, 8],
 *   [9,10,11,12]
 * ]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void print_horizontal(int ** matrix, int m_rows, int m_cols, int row_index, int col_start_index, int col_end_index, int inc, int * res_arr, int *res_start_index)
{
	if (inc < 0 && col_start_index <= col_end_index) return;
	if (inc > 0 && col_start_index >= col_end_index) return;
	int * row = matrix[row_index];
	for (int i = col_start_index; i != col_end_index; i += inc)
	{
		res_arr[*res_start_index] = row[i];
		*res_start_index = *res_start_index + 1;
	}
}

void print_vertical(int ** matrix, int m_rows, int m_cols, int col_index, int row_start_index, int row_end_index, int inc, int * res_arr, int *res_start_index)
{
	if (inc < 0 && row_start_index <= row_end_index) return;
	if (inc > 0 && row_start_index >= row_end_index) return;
	for (int i = row_start_index; i != row_end_index; i += inc)
	{
		int * row = matrix[i];
		int val_to_copy = row[col_index];
		res_arr[*res_start_index] = val_to_copy;
		*res_start_index = *res_start_index + 1;
	}
}

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	if (!matrix || !matrixSize || !returnSize || !(*matrixColSize)) return NULL;
	/* matrixSize = number of rows */
	int m_rows = matrixSize;
	/* matrixColSize = number of columns */
	int m_cols = *matrixColSize;
	*returnSize = matrixSize * (*matrixColSize);
	int * res_arr = (int *) malloc(sizeof(int) * (*returnSize));
	int top_left_x = 0, top_left_y = 0, top_right_x = m_cols, top_right_y = 0;
	int bottom_left_x = 0, bottom_left_y = m_rows, bottom_right_x = m_cols, bottom_right_y = m_rows;
	int res_start_index = 0;
	while (top_left_y < bottom_left_y)
	{
		print_horizontal(matrix, m_rows, m_cols, top_left_y, top_left_x, top_right_x, +1, res_arr, &res_start_index);

		if (top_right_x-1 >= top_left_x)
		{
			print_vertical(matrix, m_rows, m_cols, top_right_x - 1, top_right_y + 1, bottom_right_y, +1, res_arr, &res_start_index);
		}

		if (bottom_right_y-1 > top_left_y)
		{
			print_horizontal(matrix, m_rows, m_cols, bottom_right_y-1, bottom_right_x-2, bottom_left_x-1, -1, res_arr, &res_start_index);
		}

		if (bottom_left_x < top_right_x - 1)
		{
			print_vertical(matrix, m_rows, m_cols, bottom_left_x, bottom_left_y-2, top_left_y , -1, res_arr, &res_start_index);
		}

		top_left_x ++; top_left_y++; top_right_x--;top_right_y++;
		bottom_left_x ++; bottom_left_y--; bottom_right_x--; bottom_right_y--;
	}
	return res_arr;
}


void print_int_arr(int * arr, int arr_sz)
{
	if (!arr || !arr_sz) return;
	printf("%d",arr[0]);
	for (int i = 1; i < arr_sz; i++)
	{
		printf(", %d", arr[i]);
	}
	printf("\n");
}

int main()
{
	int ** matrix = (int**) malloc(sizeof(int *) * 3);
	matrix[0] = (int*) malloc(sizeof(int) * 4); matrix[0][0] = 1;matrix[0][1] = 2;matrix[0][2] = 3;matrix[0][3] = 4;
	matrix[1] = (int*) malloc(sizeof(int) * 4); matrix[1][0] = 5;matrix[1][1] = 6;matrix[1][2] = 7;matrix[1][3] = 8;
	matrix[2] = (int*) malloc(sizeof(int) * 4); matrix[2][0] = 9;matrix[2][1] = 10;matrix[2][2] = 11;matrix[2][3] = 12;
	int returnSize, matrixColSize = 4;
	int *res = spiralOrder(matrix, 3, &matrixColSize, &returnSize);
	print_int_arr(res, returnSize);

	matrix = (int**) malloc(sizeof(int *) * 2);
	matrix[0] = (int*) malloc(sizeof(int) * 4); matrix[0][0] = 1;matrix[0][1] = 2;matrix[0][2] = 3;matrix[0][3] = 4;
	matrix[1] = (int*) malloc(sizeof(int) * 4); matrix[1][0] = 5;matrix[1][1] = 6;matrix[1][2] = 7;matrix[1][3] = 8;
	//matrix[2] = (int*) malloc(sizeof(int) * 4); matrix[2][0] = 9;matrix[2][1] = 10;matrix[2][2] = 11;matrix[2][3] = 12;
	matrixColSize = 4;
	res = spiralOrder(matrix, 2, &matrixColSize, &returnSize);
	print_int_arr(res, returnSize);

	matrix = (int**) malloc(sizeof(int *) * 4);
	matrix[0] = (int*) malloc(sizeof(int) * 1); matrix[0][0] = 1;//matrix[0][1] = 2;matrix[0][2] = 3;matrix[0][3] = 4;
	matrix[1] = (int*) malloc(sizeof(int) * 1); matrix[1][0] = 5;//matrix[1][1] = 6;matrix[1][2] = 7;matrix[1][3] = 8;
	matrix[2] = (int*) malloc(sizeof(int) * 1); matrix[2][0] = 9;//matrix[2][1] = 10;matrix[2][2] = 11;matrix[2][3] = 12;
	matrix[3] = (int*) malloc(sizeof(int) * 1); matrix[3][0] = 13;//matrix[2][1] = 10;matrix[2][2] = 11;matrix[2][3] = 12;
	matrixColSize = 1;
	res = spiralOrder(matrix, 4, &matrixColSize, &returnSize);
	print_int_arr(res, returnSize);



	return 0;
}
