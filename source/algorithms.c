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
	HashTable_p esplored = hash_table_create(HASHMAP_INITIAL_SIZE);	
	while (!empty(frontier)){
		node = (IA_Node*)pop_fifo(frontier);
		hash_table_insert(esplored, (void*)&(node->node_state->id), sizeof(IA_Node), (void*)&(node->node_state), &hashing, problem->state_compare);
		actions = problem->transition_functions(node->node_state);
		while(!empty(actions)){
			temp_node = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));
			if (!is_present(frontier, (void*)temp_node, node_equals)){
				if (hash_table_search(esplored, (void*)&node->node_state->id, hashing, problem->state_compare) != NULL){	
					if (problem->goal_test(temp_node->node_state)){
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


struct IA_Node* depth_limited_search(struct Problem* problem, int limit){
	struct IA_Node* root = new_ia_node();
	root->node_state = problem->initial_state;
	return dls_recursive(root,problem,limit);
}

struct IA_Node* dls_recursive (struct IA_Node* node, struct Problem* problem, int limit){
	if (problem->goal_test(node->node_state))
		return node;
	else {
		if (limit == 0){
			return (struct IA_Node*)1;
		} else {
			Boolean cutoff_occured = false;
			struct IA_Node* ret = NULL;
			struct IA_Node* child = NULL;
			List* actions = problem->transition_functions(node->node_state);
			while(!empty(actions)){
				child = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));
				ret = dls_recursive(child,problem,limit-1);
				if (CUTOFF(ret)){
					clean_ia_node(child);
					cutoff_occured = true; //è necessario?
				}
				else 
					if (!FAILURE(ret)) 
						return ret;
			}
			if (cutoff_occured){
				return (struct IA_Node*)1;
			}
			else
				return NULL;
		}
	}
}

struct IA_Node* iterative_deepening_search(struct Problem* problem){
	long long unsigned int i = 0; //per raggiungere il livello di profondità maggiore possibile
	struct IA_Node* result = depth_limited_search(problem,i);
	
	for (; CUTOFF(result); i++){ //se la ricerca si interrompe per limiti di profondità, ne lanciamo una con profondità maggiore
		result = depth_limited_search(problem,i);
	}
	problem->depth_solution = i-1;
	return result;
}

struct IA_Node* uniform_cost_search(struct Problem* problem){return NULL;}
/*
//non ben testata
	struct IA_Node* node = new_ia_node();
	List* actions = NULL;
	struct IA_Node* child_node = NULL;
	node->node_state = problem->initial_state;
	pr_heap* frontier = new_pr_list();
	pr_push(frontier,node->path_cost,(void*)node);
	HashTable_p esplored = hash_table_create(HASHMAP_INITIAL_SIZE);	
	
	while (!pr_empty(frontier)){ 
		node = (struct IA_Node*)pr_pop(frontier); //chooses the lowest-cost node in frontier 
		if (problem->goal_test(node->node_state)){
			pr_clean_list(frontier);
			hash_table_destroy(esplored);
			return node;
		}
		hash_table_insert(esplored, (void*)&(node->node_state->id), sizeof(IA_Node), (void*)&(node->node_state), &hashing, problem->state_compare);
		actions = problem->transition_functions(node->node_state); 
		while(!empty(actions)){
			child_node = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));	
  			if (hash_table_search(esplored, (void*)&child_node->node_state->id, hashing, problem->state_compare) == NULL || pr_ispresent(frontier,(void*)child_node, node_equals) == NULL )
				pr_push(frontier,child_node->path_cost,(void*)child_node);
		}
	}
	return NULL;
}
*/

/*
struct IA_Node* AStar(struct Problem* problem){
	HashTable_p Closed = hash_table_create(HASHMAP_INITIAL_SIZE);
	pr_heap* Open = new_pr_list();
	struct IA_Node* node = new_ia_node();
	struct IA_Node* child = NULL;
	struct IA_Node* temp_node = NULL;
	
	node->node_state = problem->initial_state;
	node->path_cost = node->heuristic_Cost;
	Boolean found = false;

	pr_push(Open,node->total_cost,(void*)node);
	while( !pr_empty(Open) && !found ){
		node = (struct IA_Node*)pr_pop(Open);
		//non posso inserire solo lo stato sta volta hash_table_insert(Closed, (void*)&(node->node_state->id), sizeof(IA_Node), (void*)&(node->node_state), &hashing, problem->state_compare);
		if (problem->goal_test(node->node_state)){
			found = true;
			hash_table_destroy(Closed);
			pr_clean_list(Open);
		} else {
			List* actions = problem->transition_functions(node->node_state);
			while(!empty(actions)){
				child = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));
				temp_node = hash_table_search(esplored, (void*)&node->node_state->id, hashing, problem->state_compare);
				if (temp_node != NULL)
					if (child->total_cost < temp_node->total_cost)


				//if (//!pr_ispresent(Open,(void*)child_node, node_equals) && // == NULL)
					pr_push(Open,node->total_cost,(void*)child);
				else {

				}
			}
		}

	}

}
*/
// nelle hashtable inserisco i nodi ma il compare lo devo fare sugli stati. Nodi diversi che hanno uno stesso stato. Mentre ora verifico solo se due nodi hanno lo stesso id e non mi serve a nulla
// quando verifico se il nuovo peso è minore di quello registrato in precedenza devo farlo prendendo il peso del child e il peso registrato nel nodo in hash con lo stesso stato del child
// idem per la ricerca sulle liste che deve tornare un puntatore all'ogetto trovato