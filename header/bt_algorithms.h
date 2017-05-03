#define __BT_ALGORITHMS__

#ifndef __NODE__
	#include <node.h>
#endif

#include "priority_list.h"
#include "redblack_tree.h"

#define HASHMAP_INITIAL_SIZE 256

#define FAILURE(x) ((void*)(x) == (void*)0)
#define CUTOFF(x) ((void*)(x) == (void*)1)


struct IA_Node* bt_breadth_search(struct Problem* problem);
struct IA_Node* bt_deep_limited_search(struct Problem* problem, int lim);
struct IA_Node* bt_dls_recursive (struct IA_Node* node, struct Problem* problem, int limit);
struct IA_Node* bt_iterative_deepening_search(struct Problem* problem);
struct IA_Node* bt_uniform_cost_search(struct Problem* problem);
struct IA_Node* bt_AStar(struct Problem* problem);
