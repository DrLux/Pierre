#include <pierre.h>


int main(){
    struct Problem* problem = new_eight_puzzle(); 
    struct State* puzzle = problem->initial_state;

    problem->heuristic(puzzle);
    struct Action* moves = NULL;
    puts("Iniziamo");
    List* list = problem->transition_functions(puzzle);

    while(!empty(list)){
        moves = (Action*)pop_fifo(list);
        problem->heuristic(moves->move(puzzle));
    }
}

void print_solution (struct IA_Node* node, struct Problem* problem){
	if (node != NULL){
        int num_state = 0;
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); //sono molti di più di quelli esplorati perche non esploro nodi con gli stessi stati
        printf("\n\t ** Soluzione ** \n");
        
        while (node != NULL){
            printf("\n\t ** State N. %d ** \n", num_state++);
            problem->print_state((void*)node->node_state);
            node = node->parent;
        }
	} else
		puts("La soluzione non è stata trovata");
}


void resolve_breadth_search(struct Problem* problem){
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

void resolve_depth_limited_search(struct Problem* problem){
    struct IA_Node* node_solution = depth_limited_search(problem,problem->depth_solution); 
    if (FAILURE(node_solution))
        puts("La ricerca in Profondità Limitata non ha prodotto risultati.");
    if (CUTOFF(node_solution))
        printf("La soluzione non è stata trovata entro un limite di %ld nodi.\n", problem->depth_solution);
    else{
        puts("Problema risolto con Ricerca in Profondità Limitata");
        print_solution(node_solution,problem);
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