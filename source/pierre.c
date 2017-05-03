#include <pierre.h>

int main(){
    struct Problem* problem_lake = new_lake();
    resolve_bt_deep_limited_search(problem_lake);
    resolve_bt_uniform_cost_search(problem_lake);
    resolve_bt_iterative_deepening_search(problem_lake);
    resolve_bt_breadth_search(problem_lake);
    struct Problem* problem_puzzle = new_eight_puzzle();
    resolve_bt_astar(problem_puzzle);
    problem_puzzle = new_eight_puzzle();
    resolve_bt_astar(problem_puzzle);
    problem_puzzle = new_eight_puzzle();
    resolve_bt_astar(problem_puzzle);
    return 0;
}

void print_solution (struct IA_Node* node, struct Problem* problem){
	if (node != NULL){
        int num_state = 0;
        
        List* solution = new_list();
        
        while(node != NULL){
            push(solution,(void*)node);
            node = node->parent;
        }
        
        printf("\n\t ** Soluzione da %d stati ** \n", size(solution));
        
        while (!empty(solution)){
            printf("\n\t ** State N. %d ** \n", num_state++);
            node = (struct IA_Node*)pop_lifo(solution);
            problem->print_state(node->node_state);
        }

	} else
		puts("La soluzione non è stata trovata");
}


/*void resolve_breadth_search(struct Problem* problem){
    struct IA_Node* node_solution = breadth_search(problem);
    if (node_solution != NULL){
        puts("Problema risolto con Ricerca in Ampiezza");
        print_solution(node_solution, problem);
    } 
    else 
        puts("La Ricerca in Ampiezza non trovato risultati.");
    
    node_reset_count();
    state_reset_count();    
}

void resolve_deep_limited_search(struct Problem* problem){
    struct IA_Node* node_solution = deep_limited_search(problem,problem->depth_solution); 
    if (FAILURE(node_solution)){
        puts("La ricerca in Profondità Limitata non ha prodotto risultati.");
    } else {
        if (CUTOFF(node_solution))
            printf("La soluzione non è stata trovata entro un limite di %ld nodi.\n", problem->depth_solution);
        else{
            puts("Problema risolto con Ricerca in Profondità Limitata");
            print_solution(node_solution,problem);
        }
    }
    node_reset_count();
    state_reset_count();
}

void resolve_iterative_deepening_search(struct Problem* problem){
    struct IA_Node* node_solution = iterative_deepening_search(problem); 
    if (FAILURE(node_solution))
        puts("La ricerca in Profondità Iterativa non ha prodotto risultati.");
    else {
        puts("Problema risolto con Ricerca in Profondità Iterativa");
        printf("Il risultato è stato trovato ad una profondita paria a: %ld\n",problem->depth_solution);
        print_solution(node_solution,problem);
    }
    node_reset_count();
    state_reset_count();
}

void resolve_uniform_cost_search(struct Problem* problem){
    struct IA_Node* node_solution = uniform_cost_search(problem);
    if (node_solution != NULL){
         puts("Problema risolto con la Riceca a Costo Uniforme");
        print_solution(node_solution, problem);
    }
    else    
        puts("La Riceca a Costo Uniforme non ha prodotto risultati.");
    node_reset_count();
    state_reset_count();
}

void resolve_astar(struct Problem* problem){
    struct IA_Node* node_solution = AStar(problem);
    if (node_solution != NULL){
        puts("Problema risolto con A*");
        print_solution(node_solution, problem);
    }
    else    
        puts("A* non ha prodotto risultati.");
    node_reset_count();
    state_reset_count();
}
*/











void resolve_bt_breadth_search(struct Problem* problem){
    struct IA_Node* node_solution = bt_breadth_search(problem);
    if (node_solution != NULL){
        puts("\n Problema risolto con Ricerca in Ampiezza");
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); //sono molti di più di quelli esplorati perche non esploro nodi con gli stessi statiprintf("Stati generati: %ld\n", get_num_states()); 
    } 
    else 
        puts("La Ricerca in Ampiezza non trovato risultati.");
    
    node_reset_count();
    state_reset_count();    
}

void resolve_bt_deep_limited_search(struct Problem* problem){
    struct IA_Node* node_solution = bt_deep_limited_search(problem,problem->depth_solution); 
    if (FAILURE(node_solution)){
        puts("La ricerca in Profondità Limitata non ha prodotto risultati.");
    } else {
        if (CUTOFF(node_solution))
            printf("La soluzione non è stata trovata entro un limite di %ld nodi.\n", problem->depth_solution);
        else{
            puts("\n Problema risolto con Ricerca in Profondità Limitata");
            printf("Stati generati: %ld\n", get_num_states()); 
            printf("Nodi generati: %ld\n", get_num_nodes()); //sono molti di più di quelli esplorati perche non esploro nodi con gli stessi stati
        }
    }
    node_reset_count();
    state_reset_count();
}

void resolve_bt_iterative_deepening_search(struct Problem* problem){
    struct IA_Node* node_solution = bt_iterative_deepening_search(problem); 
    if (FAILURE(node_solution))
        puts("La ricerca in Profondità Iterativa non ha prodotto risultati.");
    else {
        puts("\n Problema risolto con Ricerca in Profondità Iterativa");
        printf("Il risultato è stato trovato ad una profondita paria a: %ld\n",problem->depth_solution);
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); //sono molti di più di quelli esplorati perche non esploro nodi con gli stessi stati
    }
    node_reset_count();
    state_reset_count();
}

void resolve_bt_uniform_cost_search(struct Problem* problem){
    struct IA_Node* node_solution = bt_uniform_cost_search(problem);
    if (node_solution != NULL){
        puts("\n Problema risolto con la Riceca a Costo Uniforme");
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); //sono molti di più di quelli esplorati perche non esploro nodi con gli stessi stati
    }
    else    
        puts("La Riceca a Costo Uniforme non ha prodotto risultati.");
    node_reset_count();
    state_reset_count();
}

void resolve_bt_astar(struct Problem* problem){
    struct IA_Node* node_solution = bt_AStar(problem);
    if (node_solution != NULL){
        puts("\n Problema risolto con A*");
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); //sono molti di più di quelli esplorati perche non esploro nodi con gli stessi stati
        print_solution(node_solution, problem);
    }
    else    
        puts("A* non ha prodotto risultati.");
    node_reset_count();
    state_reset_count();
}
