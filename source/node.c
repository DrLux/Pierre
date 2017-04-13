#include <node.h>

long int id_nodes = 0;


IA_Node* new_ia_node() {
    struct IA_Node* new_node = (IA_Node*)calloc(1,sizeof(IA_Node));;
    new_node->id = id_nodes++;
    new_node->node_state = NULL; 
    new_node->parent = NULL;
    new_node->node_action = NULL;
    new_node->path_cost = 0;
    new_node->heuristic_Cost = 0;
    new_node->total_cost = 0;
    new_node->child_ia_node = &child_ia_node;
    return new_node;
}

struct IA_Node* child_ia_node(struct Problem* problem, struct IA_Node* actual, struct Action* new_step){
    struct IA_Node* child = new_ia_node(); 
	child->node_state = new_step->move(actual->node_state);
	child->parent = actual;
	child->node_action = new_step;
	child->path_cost = problem->step_cost(actual->node_state, actual->path_cost);
	child->heuristic_Cost = problem->heuristic(actual->node_state);
    child->total_cost = child->heuristic_Cost + child->path_cost;
	return child;
}


int compare_node_id(void* node1, void* node2){
    int ret = false;
    if (node1 != NULL && node2 != NULL){
        ret = (((IA_Node*)node1)->id == ((IA_Node*)node2)->id);
    }
    return ret;
}

//negativo se il primo è minore del secondoa
int compare_node_cost(void* node1, void* node2) {
    float i1 =  ((IA_Node*)node1)->total_cost;
    float i2 =  ((IA_Node*)node2)->total_cost;

    if (i1 < i2) return -1;
    if (i1 == i2) return 0;

    return 1;
}


int compare_node_state(void* node1, void* node2){
    return state_compare( ((struct IA_Node*)node1)->node_state, ((struct IA_Node*)node2)->node_state);
}

void node_reset_count(){
    id_nodes = 0;
}

long int get_num_nodes(){
    return id_nodes;
}

void clean_ia_node(struct IA_Node* actual){
    free((void*)actual);
}