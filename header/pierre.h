#define __PIERRE__

#ifndef __ALGORITHMS__
	#include <algorithms.h>
#endif

void print_solution (struct IA_Node* node, struct Problem* problem);
void resolve_uniform_cost_search(struct Problem* problem);
void resolve_iterative_deepening_search(struct Problem* problem);
void resolve_deep_limited_search(struct Problem* problem);
void resolve_breadth_search(struct Problem* problem);
void resolve_astar(struct Problem* problem);