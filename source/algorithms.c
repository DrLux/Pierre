#include <algorithms.h>

//funzione di hashing
//con le HASH si parla di ID_STATO. Con le liste di id_nodo
int hashing(void* valKey, int arraySize){
  //long int* intKey = (long int*) valKey;
  ///return *intKey % arraySize;
  return 1;
}

//se il return è NULL allora ha fallito
struct IA_Node* breadth_search(struct Problem* problem){
	struct IA_Node* node = new_ia_node();
	node->node_state = problem->initial_state;
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
			if (!is_present(frontier, (void*)child, compare_node_state)){
				if (hash_table_search(esplored, (void*)child->node_state, hashing, problem->state_compare) == NULL){	
					if (problem->goal_test(child->node_state)){
						clean_list(frontier);
						hash_table_destroy(esplored);
						return child;
					}
					push(frontier,child);
				}
			} 
		}

	}
	return NULL;
}


struct IA_Node* deep_limited_search(struct Problem* problem, int lim){
	HashTable_p esplored = hash_table_create(HASHMAP_INITIAL_SIZE);	//registro tutti i nodi che visito, per evitare ripetizioni
	List* frontier = new_list();
	List* actions = NULL; //lista di azioni che da uno stato, generano gli stati successori
	struct IA_Node* node = new_ia_node(); //nodo attuale
	struct IA_Node* child = NULL; //nodo successore
	int limit = lim;
	node->node_state = problem->initial_state;

	if (problem->goal_test(node->node_state)) 
		return node;
	push(frontier,(void*)node);
	
	while (!empty(frontier)){ //finche non ho più nodi in frontiera da esplorare
		node = (IA_Node*)pop_lifo(frontier);
		limit--; //scendo di un livello di profondita
		hash_table_insert(esplored, (void*)node->node_state, sizeof(IA_Node), (void*)node->node_state, &hashing, problem->state_compare);	
		actions = problem->transition_functions(node->node_state); //genero le possibili azioni	
		while(!empty(actions)){ //per ogni azione possibile a partire da quello stato
			child = node->child_ia_node(problem,node, (Action*)pop_lifo(actions)); //genero un nodo successore
			if (!is_present(frontier, (void*)child, compare_node_state)){//verifico che non ci siano nodi fratelli/genitori uguali
				if (hash_table_search(esplored, (void*)child->node_state, hashing, problem->state_compare) == NULL){ //verifico anche che il nuovo stato non sia uguale ad uno visitato in precedenza
					if (problem->goal_test(child->node_state)){ //se ho trovato il risultato pulisco le risore e resituisco il nodo
						clean_list(frontier);
						hash_table_destroy(esplored);
						return child;
					}
					if (limit >= 0){ //se posso scendere di un ulteriore livello 
						push(frontier,child); //aggiungo il nuovo nodo in frontiera
						limit--; //devo incrementare due volte perche rimuovendo il nodo generatore rialzo il limite
					}
				}
			} 
		}
		limit++; //per ogni cammino che si conclude, rialzo il limite
	}
	if (limit <= 0)
		return (struct IA_Node*)1; //se la ricerca è stata interrotta dal limite restituisco questa informazione
	return NULL; //altrimenti riporto il fallimento
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
					cutoff_occured = true; 
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
	struct IA_Node* result = deep_limited_search(problem,i);

	for (; CUTOFF(result); i++){ //se la ricerca si interrompe per limiti di profondità, ne lanciamo una con profondità maggiore
		result = deep_limited_search(problem,i);
	}

	problem->depth_solution = i-1; //aggiorno il valore di profondità alla struct problema
	return result;
}

struct IA_Node* uniform_cost_search(struct Problem* problem){
	List* actions = NULL;
	Pr_List* frontier = new_pr_list();
	HashTable_p esplored = hash_table_create(HASHMAP_INITIAL_SIZE);	
	struct IA_Node* node = new_ia_node();
	struct IA_Node* child_node = NULL;
	struct IA_Node* search_node = NULL;
	node->node_state = problem->initial_state;
	
	pr_insert(frontier,(void*)node);
	while (!pr_empty(frontier)){ 
		node = (struct IA_Node*)pr_pop_min(frontier,compare_node_cost); //estraggo il nood con il costo minore
		if (problem->goal_test(node->node_state)){
			pr_destroy(frontier);
			hash_table_destroy(esplored);
			return node;
		}
		hash_table_insert(esplored, (void*)node->node_state, sizeof(IA_Node), (void*)node->node_state, &hashing, problem->state_compare);
		actions = problem->transition_functions(node->node_state); 
		while(!empty(actions)){
			child_node = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));	
  			if (hash_table_search(esplored, (void*)child_node->node_state, hashing, problem->state_compare) == NULL){//se è un nodo già esplorato non faccio nulla e vado direttamente a generare i prossimi
				search_node = pr_isPresent(frontier,(void*)child_node, compare_node_cost); //cerco anche nella frontiera
				if (search_node == NULL){ //se non è neanche in frontiera, lo aggiungo
					pr_insert(frontier,(void*)child_node);
				} else{ 
					if (child_node->total_cost < search_node->total_cost){ //se il nuovo nodo è migliore del nodo in frontiera, li sostituisco
						search_node->parent = child_node->parent;
						search_node->total_cost = child_node->total_cost;
					}
				}
  			}
		}
	}
	return NULL;
}

struct IA_Node* AStar(struct Problem* problem){
	HashTable_p Closed = hash_table_create(HASHMAP_INITIAL_SIZE);
	Pr_List* Open = new_pr_list();
	struct IA_Node* node = new_ia_node();
	struct IA_Node* child = NULL;
	struct IA_Node* search_open = NULL;
	struct IA_Node* search_closed = NULL;
	
	node->node_state = problem->initial_state;
	node->path_cost = node->heuristic_Cost;
	Boolean found = false;

	problem->print_state(node->node_state);

	pr_insert(Open,(void*)node);
	while( !pr_empty(Open) && !found ){
		node = (struct IA_Node*)pr_pop_min(Open,&compare_node_cost);	
		hash_table_insert(Closed, (void*)node->node_state, sizeof(IA_Node), (void*)node, hashing, problem->state_compare);		
		if (problem->goal_test(node->node_state)){
			found = true;
		} else {
			List* actions = problem->transition_functions(node->node_state);
			while(!empty(actions)){ //genera tutti i nodi figli
				child = node->child_ia_node(problem,node, (Action*)pop_fifo(actions));//genero un nuovo stato
				search_open = pr_isPresent(Open,(void*)child, compare_node_state); //verifica che lo stato del nodo generato non sia già nella lista dei nodi da esplorare
				if (search_open != NULL && child->total_cost < search_open->total_cost){ //se hai trovato un modo più efficiente di raggiungere uno stato già presente nella lista dei nodi da esplorare
					search_open->total_cost = child->total_cost; //aggiorna i costi del nodo in lista
					search_open->parent = child->parent; //aggiorna il percorso per arrivare al nodo in lista
				} 
				search_closed = hash_table_search(Closed, (void*)child->node_state, hashing, problem->state_compare); //cerca lo stato generato tra gli stati gia visitati
				if (search_closed != NULL && child->total_cost < search_closed->total_cost){ //se avevi registrato un percorso di arrivo obsoleto per questo stato		
					hash_table_delete(Closed, (void*)search_closed->node_state, hashing, problem->state_compare); //rimuovi dalla lista CLOSED
					pr_insert(Open,(void*)child); //aggiungi il nodo trovato in Open con il percorso aggiornato.
				}
				if (search_open == NULL && search_closed == NULL){
					pr_insert(Open,(void*)child);
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



/*struct IA_Node* secret_hash(struct Problem* problem){
	HashTable_p hash = hash_table_create(HASHMAP_INITIAL_SIZE);
	struct IA_Node* node = new_ia_node();
	List* frontier = new_list();
	node->node_state = problem->initial_state;

	
	node->node_state = lake_move_man(node->node_state);
	printf("Lo stato vale: %d\n", hashing((void*)extract_lake_state(node->node_state),256));
	problem->print_state(node->node_state);	
	
	/*node->node_state = lake_move_man(node->node_state);
	printf("Lo stato vale: %d\n", *((int*)extract_lake_state(node->node_state)));
	problem->print_state(node->node_state);	
	
	node->node_state = lake_move_man_sheep(node->node_state);
	printf("Lo stato vale: %d\n", *((int*)extract_lake_state(node->node_state)));
	problem->print_state(node->node_state);	

	node->node_state = lake_move_man_sheep(node->node_state);
	printf("Lo stato vale: %d\n", *((int*)extract_lake_state(node->node_state)));
	problem->print_state(node->node_state);	

	node->node_state = lake_move_man_wolf(node->node_state);
	printf("Lo stato vale: %d\n", *((int*)extract_lake_state(node->node_state)));
	problem->print_state(node->node_state);	

	node->node_state = lake_move_man(node->node_state);
	printf("Lo stato vale: %d\n", *((int*)extract_lake_state(node->node_state)));
	problem->print_state(node->node_state);	
	
	node->node_state = lake_move_man_sheep(node->node_state);
	printf("Lo stato vale: %d\n", *((int*)extract_lake_state(node->node_state)));
	problem->print_state(node->node_state);	


	return NULL;
}*/