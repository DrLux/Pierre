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
  			if (hash_table_search(esplored, (void*)&child_node->node_state->id, hashing, problem->state_compare) == NULL || pr_ispresent(frontier,(void*)child_node, node_equals) == NULL )
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
		node = (struct IA_Node*)pr_pop_min(Open,problem->state_compare);
		hash_table_insert(Closed, (void*)node->node_state, sizeof(IA_Node), (void*)node, &hashing, problem->state_compare);
		if (problem->goal_test(node->node_state)){
			found = true;
		} else {
			List* actions = problem->transition_functions(node->node_state);
			while(!empty(actions)){ //genera tutti i nodi figli
				child = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));		
				search_node = hash_table_search(Closed, (void*)&node->node_state, hashing, problem->state_compare); //cerca lo stato generato tra gli stati gia visitati
				if (search_node != NULL && child->total_cost < search_node->total_cost){ // //se hai trovato un modo più efficente di arrivare ad un vecchio stato rimettilo nella lista OPEN con i dati aggiornati			
						search_node->total_cost = child->total_cost;
						search_node->parent = child->parent;
						hash_table_delete(Closed, (void*)&search_node->node_state, hashing, problem->state_compare); //rimuovo dalla lista CLOSED
						pr_insert(Open,(void*)search_node); //aggiungi il nodo trovato in Open
				} else {
					search_node = pr_isPresent(Open,(void*)&node->node_state->id, problem->state_compare); //verifica che lo stato del nodo generato non sia già nella lista dei nodi da esplorare
					if (search_node != NULL && child->total_cost < search_node->total_cost){ //se hai trovato un modo più efficiente di raggiungere uno stato già presente nella lista dei nodi da esplorare
						search_node->total_cost = child->total_cost;
						search_node->parent = child->parent;
					} else { //Se lo stato generato è nuovo 
						pr_insert(Open,(void*)child); //aggiungi alla lista dei nodi da esplorare (OPEN)
					}
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


// nelle hashtable inserisco i nodi ma il compare lo devo fare sugli stati. Nodi diversi che hanno uno stesso stato. Mentre ora verifico solo se due nodi hanno lo stesso id e non mi serve a nulla
// quando verifico se il nuovo peso è minore di quello registrato in precedenza devo farlo prendendo il peso del child e il peso registrato nel nodo in hash con lo stesso stato del child
// idem per la ricerca sulle liste che deve tornare un puntatore all'ogetto trovato