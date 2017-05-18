#include <pierre.h>

int main(){
    struct Problem* problem = NULL;
    struct IA_Node* node_solution = NULL;
    int scelta_menu = 1;
    while (scelta_menu != 0){
        puts("\nProblemi disponibili:");
        puts("1) Problema del lago");
        puts("2) 8-Puzzle");
        printf("\nScegli quale problema risolvere: ");
        if (scanf("%d", &scelta_menu));  
        switch(scelta_menu){
            case 1:
                problem = new_lake();
            break;
            case 2:
                problem = new_eight_puzzle();
            break;
            default:
                scelta_menu = 0;
            break;
        }
        if (scelta_menu != 0){
            puts("\nAlgoritmi di risoluzione disponibili:");
            puts("1) Ricerca in ampiezza");
            puts("2) Ricerca in profondità limitata");
            puts("3) RIcerca in pronfondità limitata iterativa");
            puts("4) RIcerca a costo uniforme");
            puts("5) Ricerca informata: A*");
            printf("\nScegli quale utilizzare: ");
            if (scanf("%d", &scelta_menu)); 
            switch(scelta_menu){
                case 1:
                    resolve_bt_breadth_search(problem,node_solution);
                break;
                case 2:
                    printf("\nInserire la massima profondità raggiungibile (0 per usare quella di default): ");
                    long int profondita = 0;
                    if (scanf("%ld", &profondita));
                    if (profondita != 0)  
                        problem->depth_solution = profondita;
                    resolve_bt_deep_limited_search(problem,node_solution);
                break;
                case 3:
                    resolve_bt_iterative_deepening_search(problem,node_solution);
                break;
                case 4:
                    resolve_bt_uniform_cost_search(problem,node_solution);
                break;
                case 5:
                    resolve_bt_astar(problem,node_solution);
                break;
                default:
                    scelta_menu = 0;
                break;
            }
        }  
   }
    return 0;
}

void print_solution (struct IA_Node* node, struct Problem* problem){
	int stampa = 0;
    printf("\nInserire 1 per stampare il risultato, 0 per continuare: ");
    if (scanf("%d", &stampa));
        if (stampa){ 
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
}


void resolve_bt_breadth_search(struct Problem* problem, struct IA_Node* node_solution){
    node_solution = bt_breadth_search(problem);
    if (node_solution != NULL){
        puts("\n Problema risolto con Ricerca in Ampiezza");
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes());
        print_solution(node_solution, problem);   
    } 
    else 
        puts("\nLa Ricerca in Ampiezza non trovato risultati.");
    
    node_reset_count();
    state_reset_count();
}

void resolve_bt_deep_limited_search(struct Problem* problem, struct IA_Node* node_solution){
    node_solution = bt_deep_limited_search(problem,problem->depth_solution); 
    if (FAILURE(node_solution)){
        puts("\nLa ricerca in Profondità Limitata non ha prodotto risultati.");
    } else {
        if (CUTOFF(node_solution))
            printf("\nLa soluzione non è stata trovata entro un limite di %ld nodi.\n", problem->depth_solution);
        else{
            puts("\n Problema risolto con Ricerca in Profondità Limitata");
            printf("Stati generati: %ld\n", get_num_states()); 
            printf("Nodi generati: %ld\n", get_num_nodes()); 
            print_solution(node_solution, problem);
        }
    }
    node_reset_count();
    state_reset_count();
}

void resolve_bt_iterative_deepening_search(struct Problem* problem, struct IA_Node* node_solution){
    node_solution = bt_iterative_deepening_search(problem); 
    if (FAILURE(node_solution))
        puts("\nLa ricerca in Profondità Iterativa non ha prodotto risultati.");
    else {
        puts("\n Problema risolto con Ricerca in Profondità Iterativa");
        printf("Il risultato è stato trovato ad una profondita paria a: %ld\n",problem->depth_solution);
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); 
        print_solution(node_solution, problem);
    }
    node_reset_count();
    state_reset_count();
}

void resolve_bt_uniform_cost_search(struct Problem* problem, struct IA_Node* node_solution){
    node_solution = bt_uniform_cost_search(problem);
    if (node_solution != NULL){
        puts("\n Problema risolto con la Riceca a Costo Uniforme");
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); 
        print_solution(node_solution, problem);
    }
    else    
        puts("\nLa Riceca a Costo Uniforme non ha prodotto risultati.");
    node_reset_count();
    state_reset_count();
}

void resolve_bt_astar(struct Problem* problem, struct IA_Node* node_solution){
    node_solution = bt_AStar(problem);
    if (node_solution != NULL){
        puts("\n Problema risolto con A*");
        printf("Stati generati: %ld\n", get_num_states()); 
        printf("Nodi generati: %ld\n", get_num_nodes()); 
        print_solution(node_solution, problem);
    }
    else    
        puts("\nA* non ha prodotto risultati.");
    node_reset_count();
    state_reset_count();
}
