/*
 *
 * https://leetcode.com/problems/course-schedule-ii/
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 * Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
 * There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
 * Example 1: Input: 2, [[1,0]] Output: [0,1] Explanation: There are a total of 2 courses to take. To take course 1 you should have finished   
 *              course 0. So the correct course order is [0,1] .
 * Example 2: Input: 4, [[1,0],[2,0],[3,1],[3,2]] Output: [0,1,2,3] or [0,2,1,3]Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both     
 *             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. 
 *             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
 * Note:
 * The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
 * You may assume that there are no duplicate edges in the input prerequisites.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void add_edge(bool * adjacency_matrix, int num_courses, int pre_req, int req, bool *end_points)
{
	adjacency_matrix[pre_req * num_courses + req] = true;
	end_points[req] = true;
	end_points[pre_req] = false;
}

bool depth_first_traversal(bool * adjacency_matrix, int course, int num_courses, int * res, int * res_index, bool * visited, bool * outputed)
{
	if (visited[course]) return true;
	if (outputed[course]) return false;
	visited[course] = true;
	for (int i = 0; i < num_courses; i++)
	{
		if (i == course) continue;
		if (!adjacency_matrix[i*num_courses + course]) continue;
		if (depth_first_traversal(adjacency_matrix, i, num_courses, res, res_index, visited, outputed)) return true;
	}
	visited[course] = false;
	res[*res_index] = course;
	*res_index = *res_index + 1;
	outputed[course] = true;
	return false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize)
{
	if (!numCourses) {*returnSize = 0; return NULL;}
	
	bool * mem_block = (bool*) malloc(sizeof(bool) * (numCourses * numCourses + numCourses * 3));
	memset(mem_block, 0, sizeof(bool) * (numCourses * numCourses + numCourses * 2));

	bool * adjacency_matrix = mem_block;
	bool * visited = adjacency_matrix + sizeof(bool) * numCourses * numCourses;
	bool * outputed = visited + sizeof(bool) * numCourses;
	bool * end_points = outputed + sizeof(bool) * numCourses; memset(end_points, (char) true, sizeof(bool)*numCourses);
	for (int i = 0; i < prerequisitesSize; i ++)
	{
		add_edge(adjacency_matrix, numCourses, prerequisites[i][1] /*pre_req*/, prerequisites[i][0] /*req*/, end_points);
	}

	int * res = (int *) malloc(sizeof(int)*numCourses);
	int res_index = 0;
	bool cycle_detected = false;
	for (int i = 0; i < numCourses; i ++)
	{
		cycle_detected = end_points[i] && depth_first_traversal(adjacency_matrix, i, numCourses, res, &res_index, visited, outputed);
		if (cycle_detected) break;
	}

	free(mem_block);

	if (cycle_detected)
	{
		free(res);
		*returnSize = 0;
		return NULL;
	}
	else
	{
		*returnSize = numCourses;
		return res;
	}
}

void print_int_arr(int * arr, int arr_sz)
{
	if (!arr || !arr_sz) return;
	printf("[%d", arr[0]);
	for (int i = 1; i < arr_sz; i ++) printf(", %d",arr[i]);
	printf("]\n");
}

int main()
{
	int ** pre_req1 = (int**) malloc(sizeof(int*)*1);
	int p[2] = {0,1};
	pre_req1[0] = p;
	int res_size;
	int * res = findOrder(2, pre_req1, 1, NULL, &res_size);
	print_int_arr(res, res_size);


	int ** pre_req2 = (int**) malloc(sizeof(int*)*4);
	int p1[2] = {1,0}; int p2[2] = {2,0}; int p3[2] = {3,1}; int p4[2] = {3,2};
	pre_req2[0] = p1;pre_req2[1] = p2;pre_req2[2] = p3;pre_req2[3] = p4;
	res = findOrder(4, pre_req2, 4, NULL, &res_size);
	print_int_arr(res, res_size);

	int ** pre_req3 = (int**) malloc(sizeof(int*)*5);
	int p3_1[2] = {1,0}; int p3_2[2] = {2,0}; int p3_3[2] = {3,1}; int p3_4[2] = {3,2}; int p3_5[2] = {0,3};
	pre_req3[0] = p3_1;pre_req3[1] = p3_2;pre_req3[2] = p3_3;pre_req3[3] = p3_4;pre_req3[4] = p3_5;
	res = findOrder(4, pre_req3, 5, NULL, &res_size);
	print_int_arr(res, res_size);
	return 0;
}
