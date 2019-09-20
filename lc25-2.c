/*
 *
 * https://leetcode.com/problems/alien-dictionary/
 * There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you.
 * You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language.
 * Derive the order of letters in this language.
 * Example 1: Input: ["wrt","wrf", "er", "ett","rftt"] Output: "wertf"
 * Example 2: Input: ["z", "x"] Output: "zx"
 * Example 3: Input: ["z","x","z"] Output: ""  Explanation: The order is invalid, so return "".
 * Note:
 * You may assume all letters are in lowercase.
 * You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
 * If the order is invalid, return an empty string.
 * There may be multiple valid order of letters, return any one of them is fine.
 */

/*
 * Definitely a hard problem. My initial solution had a pretty bad bug (which I could have figured it out if I tested a little bit more (shame on me).
 * Took me about 1 day to get the correct solution.
 * I would have definitely failed this on an interview.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define alphabet_sz (26)
#define index_from_char(ch) ((int) (ch-'a'))

/* graph */
typedef struct graph_t
{
	char ch;
	bool visited;
	struct graph_t ** children;
} graph;

graph * node_from_char(char ch)
{
	graph * res = (graph*) malloc(sizeof(graph));
	res->visited = false;
	res->ch = ch;
	res->children = NULL;
	return res;
}

/* given the input words, this returns the distinct letters in the word */
char * return_distinct_letters_only(char *word)
{
	char * res = (char *) malloc(sizeof(char)*alphabet_sz);
	bool encountered_letters[alphabet_sz];
	memset(encountered_letters, 0, sizeof(bool)*alphabet_sz);
	for (int i = 0; word[i]; i++)
	{
		encountered_letters[index_from_char(word[i])] = true;
	}
	int res_index = 0;
	for (int i = 0; i < alphabet_sz; i ++)
	{
		if (!encountered_letters[i]) continue;
		res[res_index] = (char) (i + 'a');
		res_index ++;
	}
	res[res_index] = '\0';
	return res;
}

void add_node(graph ** list_of_end_letters, graph ** char_to_node_map, char ch)
{
	int index = index_from_char(ch);
	if (char_to_node_map[index]) return;
	graph * node = node_from_char(ch);
	list_of_end_letters[index] = node;
	char_to_node_map[index] = node;
}

void add_edge(graph ** list_of_end_letters, graph ** char_to_node_map, char smaller, char larger)
{
	int smaller_index = index_from_char(smaller), larger_index = index_from_char(larger);
	graph * smaller_node = char_to_node_map[smaller_index];
	graph * larger_node = char_to_node_map[larger_index];
	if (!smaller_node)
	{
		smaller_node = node_from_char(smaller);
		char_to_node_map[smaller_index] = smaller_node;
	}
	if (!larger_node)
	{
		larger_node = node_from_char(larger);
		char_to_node_map[larger_index] = larger_node;
	}
	if (!larger_node->children)
	{
		larger_node->children = (graph**) malloc(sizeof(graph*)*alphabet_sz);
		memset(larger_node->children, 0, sizeof(graph*) * alphabet_sz);
	}
	larger_node->children[index_from_char(smaller)] = smaller_node;
	list_of_end_letters[smaller_index] = NULL;
	list_of_end_letters[larger_index] = larger_node;
}

void lexicographical_compare(graph ** list_of_end_letters, char * prev, char * curr, graph ** char_to_nodes_map)
{
	while (*prev && *curr && *prev == *curr)
	{
		add_node(list_of_end_letters, char_to_nodes_map, *curr);
		prev ++;
		curr ++;
	}
	if (*prev && * curr)
	{
		add_edge(list_of_end_letters, char_to_nodes_map, *prev, *curr);
	}
	for (; *prev; prev++)
	{
		add_node(list_of_end_letters, char_to_nodes_map, *prev);
	}
	for (; *curr; curr++)
	{
		add_node(list_of_end_letters, char_to_nodes_map, *curr);
	}
}

bool depth_first_traversal(graph * g, char * res, int * res_index, bool * characters_printed)
{
	if (g->visited) return true;
	int ch_index = index_from_char(g->ch);
	if (characters_printed[ch_index]) return false;
	if (g->children)
	{
		for (int i = 0; i < alphabet_sz; i ++)
		{
			g->visited = true;
			if (g->children[i] && depth_first_traversal(g->children[i], res, res_index, characters_printed)) return true;
			g->visited = false;
		}
	}
	res[*res_index] = g->ch;
	*res_index = *res_index + 1;
	characters_printed[ch_index] = true;
	return false;
}

char * alienOrder(char ** words, int wordsSize)
{
	if (!words || !wordsSize) return "";
	if (wordsSize == 1) return return_distinct_letters_only(words[0]);

	/* a map from char to graph nodes */
	graph * char_to_nodes_map[alphabet_sz];
	memset(char_to_nodes_map, 0, sizeof(graph *) * alphabet_sz);

	/* the list of end letters - essentially our graph */
	graph * list_of_end_letters[alphabet_sz];
	memset(list_of_end_letters, 0, sizeof(graph*) * alphabet_sz);

	/* build the graph by reading the input */
	for (int i = 1; i < wordsSize; i ++)
	{
		lexicographical_compare(list_of_end_letters, words[i - 1], words[i], char_to_nodes_map);
	}

	char * res = (char*) malloc(sizeof(char) * (alphabet_sz+1));
	int res_index = 0;
	bool characters_printed[alphabet_sz];
	memset(characters_printed, 0, sizeof(bool)*alphabet_sz);
	for (int i = 0; i < alphabet_sz; i ++)
	{
		if (list_of_end_letters[i] && depth_first_traversal(list_of_end_letters[i], res, &res_index, characters_printed))
		{
			res[0] = '\0';
			break;
		}
	}
	res[res_index] = '\0';

	for (int i = 0; i < alphabet_sz; i ++)
	{
		if (char_to_nodes_map[i]) free(list_of_end_letters[i]);
	}

	return res;
}


int main()
{
	char * input[] = {"wrt","wrf","er","ett","rftt"};
	char * res = alienOrder(input, 5);
	printf("%s.\n", res);
	char * input2[] = {"abcdef","cde", "deexyz"};
	res = alienOrder(input2, 3);
	printf("%s.\n", res);
	char * input3[] = {"adbw","cewg", "dfef"};
	res = alienOrder(input3, 3);
	printf("%s.\n", res);
	char * input4[] = {"bsusz","rhn","gfbrwec","kuw","qvpxbexnhx","gnp","laxutz","qzxccww"};
	res = alienOrder(input4, 8);
	printf("%s.\n", res);
	char * input5[] = {"b","r","g","k","q","g","l","q"};
	res = alienOrder(input5, 8);
	printf("%s.\n", res);
	return 0;
}
