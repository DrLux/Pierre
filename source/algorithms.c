#include <algorithms.h>

//fare una struct che contiene le informazioni di debug quali:
//nodi in frontiera, stati creati, nodi creati, nodi esplorati

//funzione di hashing
//con le HASH si parla di ID_STATO. Con le liste di id_nodo
int hashing(void* valKey, int arraySize){
  long int* intKey = (long int*) valKey;
  return *intKey % arraySize;
}

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
	HashTable_p esplored = hash_table_create(256);	
	while (!empty(frontier)){
		node = (IA_Node*)pop_fifo(frontier);
		hash_table_insert(esplored, (void*)&(node->node_state->id), sizeof(IA_Node), (void*)&(node->node_state), &hashing, problem->state_compare);
		actions = problem->transition_functions(node->node_state);
		while(!empty(actions)){
			temp_node = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));
			if (!is_present(frontier, (void*)temp_node, node_equals)){
				if (hash_table_search(esplored, (void*)&node->node_state->id, hashing, problem->state_compare) != NULL){
					if (problem->goal_test(temp_node->node_state)){
						puts("");
						printf("Stati esplorati %d\n", esplored->recordInserted);
						printf("Nodi rimasti in frontiera %d nodi \n", frontier->size);
						clean_list(frontier);
						hash_table_destroy(esplored);
						return temp_node;
					}
					push(frontier,temp_node);
				} 
			} 
		}

	}
	return NULL;
}



void print_solution (struct IA_Node* node, struct Problem* problem){
	if (node != NULL){
		printf("Nodi generati: %ld\n", (new_ia_node())->id); //sono molti di più di quelli esplorati perche non esploro nodi con gli stessi stati
		List* solution = new_list();
		while (node != NULL){
			push(solution,(void*)node->node_state);
			node = node->parent;
		}
		problem->print_solution(solution);
	} else
		puts("La soluzione non è stata trovata");
}

int main(){
    struct Problem* problem = new_lake();
    print_solution(breadth_search(problem), problem);
    return 0;
}