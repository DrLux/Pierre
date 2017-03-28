#include <node.h>

int id_nodes = 1;

IA_Node* new_ia_node() {
    struct IA_Node* new_node = (IA_Node*)calloc(1,sizeof(IA_Node));;
    new_node->id = id_nodes++;
    new_node->node_state = NULL; 
    new_node->parent = NULL;
    new_node->node_action = NULL;
    new_node->path_cost = 0;
    new_node->heuristic_Cost = 0;
    new_node->child_ia_node = &child_ia_node;
    return new_node;
}

struct IA_Node* child_ia_node(struct Problem* problem, struct IA_Node* actual, struct Action* new_step){
	struct IA_Node* child = new_ia_node(); 
	child->node_state = new_step->move(actual->node_state);//da rendere void, il nuovo stato è null e non una struct vuota
	child->parent = actual;
	child->node_action = new_step;
	child->path_cost = problem->step_cost(actual->node_state, actual->path_cost);
	child->heuristic_Cost = problem->heuristic(actual->node_state);
	return child;
}

int node_equals(void* node1, void* node2){
    int ret = false;
    if (node1 != NULL && node2 != NULL){
        ret = (((IA_Node*)node1)->id == ((IA_Node*)node2)->id);
    }
    return ret;
}