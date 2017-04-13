#define __ALGORITHMS__

#ifndef __NODE__
	#include <node.h>
#endif
#include "hash_table.h"
#include "priority_list.h"

#define HASHMAP_INITIAL_SIZE 256

#define FAILURE(x) ((void*)(x) == (void*)0)
#define CUTOFF(x) ((void*)(x) == (void*)1)


struct IA_Node* breadth_search(struct Problem* problem);
void manage_goal(List* frontier, HashTable_p esplored);

struct IA_Node* depth_limited_search(struct Problem* problem, int limit);
struct IA_Node* dls_recursive (struct IA_Node* node, struct Problem* problem, int limit);
struct IA_Node* iterative_deepening_search(struct Problem* problem);
struct IA_Node* uniform_cost_search(struct Problem* problem);
struct IA_Node* AStar(struct Problem* problem);
int cost (struct IA_Node* node);