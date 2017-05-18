#define __PIERRE__

#ifndef __BT_ALGORITHMS__
	#include <bt_algorithms.h>
#endif

void print_solution (struct IA_Node* node, struct Problem* problem);
void resolve_bt_uniform_cost_search(struct Problem* problem, struct IA_Node* node_solution);
void resolve_bt_iterative_deepening_search(struct Problem* problem, struct IA_Node* node_solution);
void resolve_bt_deep_limited_search(struct Problem* problem, struct IA_Node* node_solution);
void resolve_bt_breadth_search(struct Problem* problem, struct IA_Node* node_solution);
void resolve_bt_astar(struct Problem* problem, struct IA_Node* node_solution);