#define __NODE__

#ifndef __LAKE__
	#include <problem.h>
#endif


typedef struct IA_Node {
	long int id;
	struct State* node_state;
	struct IA_Node* parent;
	struct Action* node_action;
	int path_cost;
	int heuristic_Cost;
	struct IA_Node* (*child_ia_node)(struct Problem* problem, struct IA_Node* actual, struct Action* move);
} IA_Node;

struct IA_Node* child_ia_node(struct Problem* problem, struct IA_Node* actual, struct Action* move);
//i 2 nodi sono a void perche devono avere a che fare con le liste
int node_equals(void* node1, void* node2);

IA_Node* new_ia_node();


