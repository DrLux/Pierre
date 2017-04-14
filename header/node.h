#define __NODE__

#ifndef __PROBLEM__
	#include <problem.h>
#endif

typedef int (*Comp)(void*, void*);

typedef struct IA_Node {
	long int id; //serve per la LISTA di nodi
	struct State* node_state;
	struct IA_Node* parent;
	struct Action* node_action;
	float path_cost;
	float heuristic_Cost;
	float total_cost;
	struct IA_Node* (*child_ia_node)(struct Problem* problem, struct IA_Node* actual, struct Action* move);
} IA_Node;

struct IA_Node* child_ia_node(struct Problem* problem, struct IA_Node* parent, struct Action* move);


IA_Node* new_ia_node();
void node_reset_count();
long int get_num_nodes();
int compare_node_cost(void* node1, void* node2);
int compare_node_id(void* node1, void* node2); //torna 1 quando sono uguali
int compare_node_state(void* node1, void* node2);

void clean_ia_node(struct IA_Node* actual);
