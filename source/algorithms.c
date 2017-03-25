#include <algorithms.h>

//se il return è NULL allora ha fallito
struct IA_Node* breadth_search(struct Problem* problem){
	struct IA_Node* node = new_ia_node();	
	node->node_state = problem->initial_state;
	node->path_cost = 0;
	if (problem->goal_test(node->node_state))
		return node;
	List* frontier = new_list();
	List* actions = NULL;
	struct IA_Node* temp_node = NULL;

	push(frontier,(void*)node);
	//hashmap esplored;//da completare
	while (!empty(frontier)){
		node = (IA_Node*)pop_fifo(frontier);
		//add(esplorati, node->node_state);
		actions = problem->transition_functions(node->node_state);
		while(!empty(actions)){
			temp_node = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));
			//if (figlio non in esplorati e non in frontiera){//implementare search and hashmap
				if (problem->goal_test(temp_node->node_state))
					return temp_node;
				push(frontier,temp_node);
			//}
		}

	}
	return NULL;
}


int main(){
    struct Problem* problem = new_lake();
    List* list = NULL;
    struct Action* temp_move = NULL;
    State* temp_state = NULL;


    list = problem->transition_functions(problem->initial_state);
    temp_move = (Action*)pop_fifo(list);


    while (temp_move != NULL && temp_move->move != NULL){
        temp_state = temp_move->move(problem->initial_state);
        problem->print_state(temp_state);
        temp_move = (Action*)pop_fifo(list);

    }
    return 0;
}

//Fare la print solution che prende come parametro il nodo uscito dall' algoritmo. Se è null
// stampa fallimento, altrimenti stampa la coda di soluzione