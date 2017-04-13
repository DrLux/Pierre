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
	struct IA_Node* child = NULL;
	push(frontier,(void*)node);
	HashTable_p esplored = hash_table_create(HASHMAP_INITIAL_SIZE);	
	while (!empty(frontier)){
		node = (IA_Node*)pop_fifo(frontier);		
		hash_table_insert(esplored, (void*)node->node_state, sizeof(IA_Node), (void*)node->node_state, &hashing, problem->state_compare);	
		actions = problem->transition_functions(node->node_state);	
		while(!empty(actions)){
			child = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));			
			//if (!is_present(frontier, (void*)child, compare_node_state)){
				if (hash_table_search(esplored, (void*)child->node_state, hashing, problem->state_compare) == NULL){	
					if (problem->goal_test(child->node_state)){
						clean_list(frontier);
						hash_table_destroy(esplored);
						return child;
					}
					push(frontier,child);
				} 
			//} 
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
	pr_insert(frontier,node->path_cost,(void*)node);
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
  			if (hash_table_search(esplored, (void*)&child_node->node_state->id, hashing, problem->state_compare) == NULL || pr_ispresent(frontier,(void*)child_node, compare_node_id) == NULL )
				pr_insert(frontier,child_node->path_cost,(void*)child_node);
		}
	}
	return NULL;
}
*/


struct IA_Node* AStar(struct Problem* problem){
	HashTable_p Closed = hash_table_create(HASHMAP_INITIAL_SIZE);
	Pr_List* Open = new_pr_list();
	struct IA_Node* node = new_ia_node();
	struct IA_Node* child = NULL;
	struct IA_Node* search_node = NULL;
	
	node->node_state = problem->initial_state;
	node->path_cost = node->heuristic_Cost;
	Boolean found = false;

	pr_insert(Open,(void*)node);
	while( !pr_empty(Open) && !found ){
		node = (struct IA_Node*)pr_pop_min(Open,&compare_node_cost);	
		hash_table_insert(Closed, (void*)node->node_state, sizeof(IA_Node), (void*)node, &hashing, problem->state_compare);
		if (problem->goal_test(node->node_state)){
			found = true;
		} else {
			List* actions = problem->transition_functions(node->node_state);
			while(!empty(actions)){ //genera tutti i nodi figli
				child = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));//genero un nuovo stato
				search_node = pr_isPresent(Open,(void*)child, compare_node_state); //verifica che lo stato del nodo generato non sia già nella lista dei nodi da esplorare
				if (search_node != NULL && child->total_cost < search_node->total_cost){ //se hai trovato un modo più efficiente di raggiungere uno stato già presente nella lista dei nodi da esplorare
					search_node->total_cost = child->total_cost; //aggiorna i costi del nodo in lista
					search_node->parent = child->parent; //aggiorna il percorso per arrivare al nodo in lista
				} else {
					search_node = hash_table_search(Closed, (void*)node->node_state, hashing, problem->state_compare); //cerca lo stato generato tra gli stati gia visitati
					if (search_node != NULL && child->total_cost < search_node->total_cost){ //se avevi registrato un percorso di arrivo obsoleto per questo stato		
						hash_table_delete(Closed, (void*)search_node->node_state, hashing, problem->state_compare); //rimuovi dalla lista CLOSED
					}
					pr_insert(Open,(void*)child); //aggiungi il nodo trovato in Open con il percorso aggiornato.
				}

				}

			}
		}
if (found){
	hash_table_destroy(Closed);
	pr_destroy(Open);
	return node;
} else 
	return NULL;
}



struct IA_Node* secret_hash(struct Problem* problem){
	HashTable_p hash = hash_table_create(HASHMAP_INITIAL_SIZE);
	struct IA_Node* node = new_ia_node();
	struct IA_Node* child = NULL;
	struct IA_Node* search_node = NULL;

	node->node_state = problem->initial_state;
	List* actions = problem->transition_functions(node->node_state);

	problem->print_state(node->node_state);
	hash_table_insert(hash, (void*)node->node_state, sizeof(IA_Node), (void*)node->node_state, &hashing, problem->state_compare);	


	while(!empty(actions)){
		child = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));
		hash_table_insert(hash, (void*)child->node_state, sizeof(IA_Node), (void*)child->node_state, &hashing, problem->state_compare);	
	}
	
	printf("La hash ha %d elementi\n", (int)hash->recordInserted);
		
	search_node = hash_table_search(hash, (void*)child->node_state, hashing, problem->state_compare);
	if (search_node == NULL)
		puts("non trovato");
	else
		problem->print_state(child->node_state);



	return NULL;
}