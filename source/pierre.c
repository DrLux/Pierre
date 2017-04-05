#include <pierre.h>

int main(){
    struct Problem* problem = new_lake();
    /*struct IA_Node* node_solution = breadth_search(problem);
    if (node_solution != NULL)
		print_solution(node_solution, problem);
    else	
    	puts("La breadth_search sul lake non è andata a buon fine.");*/

    /*struct IA_Node* node_solution = depth_limited_search(problem,LAKE_DLS_LIMIT); //definire LIMITE_LAKE
    if (FAILURE(node_solution))
    	puts("La ricerca non ha prodotto risultati.");
    if (CUTOFF(node_solution))
    	puts("Il limite inserito è troppo stringente.");
    else
    	print_solution(node_solution,problem);*/

    
    struct IA_Node* node_solution = iterative_deepening_search(problem); 
    if (FAILURE(node_solution))
    	puts("La ricerca non ha prodotto risultati.");
	else 
		print_solution(node_solution,problem);
    return 0;
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
