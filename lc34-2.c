/*
 * https://leetcode.com/problems/the-skyline-problem/
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct event_t
{
	int time;
	int height;
	char type;		/* 's' for start and 'e' for end */
} event;

/**********************************/
/*      HEAP BASED SOLUTION      */
/**********************************/
typedef struct heap_node_t
{
	int height, count;
} heap_node;

void swap_heap_nodes(heap_node * heap, int a, int b)
{
	heap_node tmp = heap[a];
	heap[a] = heap[b];
	heap[b] = tmp;
}

int max_height_from_heap(heap_node * heap, int heap_sz)
{
	return heap_sz ? heap[0].height : 0;
}

void bubble_up(heap_node * heap, int index)
{
	/* bubble up the new node */
	while (index)
	{
		int parent_index = (index-1) / 2;
		if (heap[parent_index].height >= heap[index].height) break;
		swap_heap_nodes(heap, parent_index, index);
		index = parent_index;
	}
}

void add_to_heap(heap_node * heap, int * heap_sz, int height)
{
	for (int i = 0; i < *heap_sz; i ++)
	{
		if (heap[i].height == height)
		{
			heap[i].count ++;
			return;
		}
	}
	int index = *heap_sz;
	*heap_sz = *heap_sz + 1;
	heap[index].height = height;
	heap[index].count = 1;
	bubble_up(heap, index);
}

void delete_from_heap(heap_node * heap, int * heap_sz, int height, bool * unique_height)
{
	*unique_height = false;
	int index = 0;
	for (; index < *heap_sz; index ++)
	{
		if (heap[index].height == height)
		{
			heap[index].count --;
			if (heap[index].count) return;
			break;
		}
	}

	*unique_height = true;
	*heap_sz = *heap_sz - 1;
	if (!(*heap_sz)) return;
	swap_heap_nodes(heap, index, *heap_sz);
	/* assert (i < heap_sz) */
	int parent_index = (index-1) / 2;
	if (heap[parent_index].height < heap[index].height)
	{
		bubble_up(heap, index);
		return;
	}
	/* bubble down the swapped node */
	while (index < *heap_sz)
	{
		int l_child_index = 2 * index + 1;
		int r_child_index = 2 * index + 2;
		if (l_child_index >= *heap_sz) break;	/* no child nodes */
		int swap_index;
		if (r_child_index >= *heap_sz)
		{
			swap_index = l_child_index;
		}
		else
		{
			swap_index = heap[r_child_index].height > heap[l_child_index].height ? r_child_index : l_child_index;
		}
		if (heap[index].height > heap[swap_index].height) break;	/* index is already bigger than both its children */
		swap_heap_nodes(heap, index, swap_index);
		index = swap_index;
	}
}

/**********************************/
/*   LINKED LIST BASED SOLUTION   */
/**********************************/

/* a linked list of heights */
/* should we keep this list sorted? */
typedef struct linked_list_t
{
	int height;
	int count;
	struct linked_list_t * next;
} linked_list;

linked_list * node_from_height(int height, linked_list * mem_alloc, int * mem_alloc_top)
{
	linked_list * res = mem_alloc+(*mem_alloc_top);
	*mem_alloc_top = *mem_alloc_top + 1;
	res->height = height;
	res->next = NULL;
	res->count = 1;
	return res;
}

linked_list * add_height(linked_list * head, int height, linked_list * mem_alloc, int * mem_alloc_top)
{
	linked_list * ll = head;
	while (ll && ll->height != height) ll = ll->next;
	if (ll)
	{
		ll->count ++;
		return head;
	}
	ll = node_from_height(height, mem_alloc, mem_alloc_top);
	ll->next = head;
	return ll;	
}

int max_height_in_list(linked_list * head)
{
	int res = 0;
	while (head)
	{
		res = res < head->height ? head->height : res;
		head = head->next;
	}
	return res;
}

linked_list * remove_height(linked_list * head, int height, bool * unique_height)
{
	if (!head)
	{
		*unique_height = true;
		return NULL;
	}
	*unique_height = false;
	linked_list * ll = head, * prev = NULL;
	while (ll && ll->height != height)
	{
		prev = ll;
		ll = ll->next;
	}
	/* assert(ll) */
	if (!ll) return head;
	ll->count --;
	if (ll->count) return head;
	*unique_height = true;
	if (prev)
	{
		prev->next = ll->next;
	}
	else
	{
		/* removal from the front */
		head = ll->next;
	}
	/*free(ll);*/
	return head;
}

void swap(event * arr, int a, int b)
{
	event tmp = arr [a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int cmp(event a, event b)
{
	if (a.time != b.time) return a.time - b.time;
	if(a.type != b.type) return b.type - a.type; 	/* want to process starts 's' before processing ends 'e' */

	/* want to add starts 's' in decreasing order, and ends 'e' in increasing order */
	if (a.type == 's') return b.height - a.height;
	else return a.height - b.height;
}

int partition_index(event * arr, int lo, int hi)
{
	event mid_point_event = arr[(lo+hi)/2];
	while (lo <= hi)
	{
		while (cmp(arr[lo], mid_point_event) < 0) lo++;
		while (cmp(mid_point_event, arr[hi]) < 0) hi--;
		if (lo <= hi)
		{
			swap(arr, lo, hi);
			lo++;
			hi--;
		}
	}
	return lo;
}

void quicksort(event * arr, int lo, int hi)
{
	/* base cases */
	if (lo >= hi) return;
	if (lo == hi-1)
	{
		if (arr[lo].time > arr[hi].time) swap(arr, lo, hi);
		return;
	}
	int pivot = partition_index(arr, lo,hi);
	quicksort(arr, lo, pivot-1);
	quicksort(arr, pivot, hi);
}

int ** add_point_to_skyline(int ** skyline, int *skyline_sz, int index, int x, int y)
{
	if (*skyline_sz <= index)
	{
		*skyline_sz = (*skyline_sz) * 2;
		skyline = realloc(skyline, (*skyline_sz) * sizeof(int *));
	}
	int * pt = (int *) malloc(sizeof(int)*2);
	pt[0] = x;
	pt[1] = y;
	skyline[index] = pt;
	return skyline;
}

int * add_column_size(int * return_column_sizes, int * return_column_sizes_sz, int index)
{
	if (*return_column_sizes_sz <= index)
	{
		*return_column_sizes_sz = (*return_column_sizes_sz) * 2;
		return_column_sizes = realloc(return_column_sizes, (*return_column_sizes_sz)*sizeof(int));
	}
	return_column_sizes[index] = 2;
	return return_column_sizes;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize, int* returnSize, int** returnColumnSizes)
{
	if (!buildings || !buildingsSize)
	{
		*returnSize = 0;
		*returnColumnSizes = NULL;
		return NULL;
	}
	event * events = (event *) malloc(sizeof(event)*2*buildingsSize);
	for (int i = 0; i < buildingsSize; i ++)
	{
		events[2*i].time = buildings[i][0];
		events[2*i].height = buildings[i][2];
		events[2*i].type = 's';
		events[2*i+1].time = buildings[i][1];
		events[2*i+1].height = buildings[i][2];
		events[2*i+1].type = 'e';
	}
	quicksort(events, 0, 2*buildingsSize - 1);
	*returnSize = 0;
	int max_height = 0;
	int res_sz = buildingsSize;
	int ** res = (int **) malloc(sizeof(int *)*buildingsSize*2);
	int return_column_sizes_sz = buildingsSize*2;
	int * return_column_sizes = (int*) malloc(sizeof(int) * return_column_sizes_sz);
	//int mem_alloc_top = 0;
	//linked_list * mem_alloc = (linked_list *) malloc(sizeof(linked_list)*buildingsSize * 2);
	int res_index = 0;
	//linked_list * heights_list = NULL;
	heap_node * heights_heap = (heap_node *) malloc(sizeof(heap_node)*buildingsSize * 2);
	int heap_sz = 0;
	for (int i = 0; i < 2 * buildingsSize; i++)
	{
		event e = events[i];
		if (e.type == 's')
		{
			if (e.height > max_height)
			{
				max_height = e.height;
				res = add_point_to_skyline( res, &res_sz, res_index, e.time, max_height);
				return_column_sizes = add_column_size(return_column_sizes, &return_column_sizes_sz, res_index);
				res_index++;
				*returnSize = *returnSize + 1;
			}
			//heights_list = add_height(heights_list, e.height, mem_alloc, &mem_alloc_top);
			add_to_heap(heights_heap, &heap_sz, e.height);
		}
		else
		{
			/* assert(e.type == 'e') */
			bool unique_height;
			//heights_list = remove_height(heights_list, e.height, &unique_height);
			delete_from_heap(heights_heap, &heap_sz, e.height, &unique_height);
			/* this if statement relies on adding events in order of time, type ('s' before 'e') and then height */
			/* maybe it would be easier to understand if we explicitly remove the items of the same height? */
			if (e.height == max_height && unique_height)
			{
				//max_height = max_height_in_list(heights_list);
				max_height = max_height_from_heap(heights_heap, heap_sz);
				res = add_point_to_skyline( res, &res_sz, res_index, e.time, max_height);
				return_column_sizes = add_column_size(return_column_sizes, &return_column_sizes_sz, res_index);
				res_index++;
				*returnSize = *returnSize + 1;
			}
		}
	}

	free(events);
	//free(mem_alloc);
	free(heights_heap);
	/* assert(!heights_list) */
	*returnColumnSizes = return_column_sizes;
	return res;
}

void print_res(int ** res, int res_sz)
{
	if (!res || !res_sz) return;
	printf("[ [%d,%d] ", res[0][0], res[0][1]);
	for (int i = 1; i < res_sz; i ++)
	{
		printf(", [%d,%d] ", res[i][0], res[i][1]);
	}
	printf("]\n");
}

int main()
{
	int rect1[] = {2,9,10};
	int rect2[] = {3,7,15};
	int rect3[] = {5,12,12};
	int rect4[] = {15,20,10};
	int rect5[] = {19,24,8};
	int * input[] = {rect1, rect2, rect3, rect4, rect5};
	int res_sz;
	int * return_column_sizes;
	int ** res = getSkyline(input, 5, NULL, &res_sz, &return_column_sizes);
	print_res(res, res_sz);
	int rect2_1[] = {2,9,10}, rect2_2[] = {3,7,15}, rect2_3[] = {4,5,11}, rect2_4[]= {6,12,12}, rect2_5[] = {15,20,10}, rect2_6[] = {19,24,8};
	int * input2[] = {rect2_1, rect2_2, rect2_3, rect2_4, rect2_5, rect2_6};
	res = getSkyline(input2, 6, NULL, &res_sz, &return_column_sizes);
	print_res(res, res_sz);
	//[[2,9,10],[3,7,15],[4,9,11],[5,12,12],[15,20,10],[19,24,8]]
	//[[2,9,10],[3,7,15],[9,10,24],[5,12,12],[15,20,10],[19,24,8]]
	int rect3_1[] = {1,2,1};
	int rect3_2[] = {1,2,2};
	int rect3_3[] = {1,2,3};
	int * input3[] = {rect3_1, rect3_2, rect3_3};
	res = getSkyline(input3, 3, NULL, &res_sz, &return_column_sizes);
	print_res(res, res_sz);
	return 0;
}

