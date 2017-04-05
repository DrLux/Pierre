#include <pierre.h>

int main(){
    /*struct Problem* problem1 = new_lake();
    struct IA_Node* node_solution1 = breadth_search(problem1);
    if (node_solution1 != NULL){
        puts("breadth_search");
		print_solution(node_solution1, problem1);
    }
    else	
    	puts("La breadth_search sul lake non è andata a buon fine.");
    
    struct Problem* problem2 = new_lake();
    struct IA_Node* node_solution2 = depth_limited_search(problem2,LAKE_DLS_LIMIT); //definire LIMITE_LAKE
    if (FAILURE(node_solution2))
    	puts("La ricerca non ha prodotto risultati.");
    if (CUTOFF(node_solution2))
    	puts("Il limite inserito è troppo stringente.");
    else{
        puts("depth_limited_search");
    	print_solution(node_solution2,problem2);
    }
    
    
    struct Problem* problem3 = new_lake();
    struct IA_Node* node_solution3 = iterative_deepening_search(problem3); 
    if (FAILURE(node_solution3))
    	puts("La ricerca non ha prodotto risultati.");
	else {
        puts("iterative_deepening_search");
		print_solution(node_solution3,problem3);
    }*/
    
    
    struct Problem* problem4 = new_lake();
    struct IA_Node* node_solution4 = uniform_cost_search(problem4);
    if (node_solution4 != NULL){
        puts("uniform_cost_search");
        print_solution(node_solution4, problem4);
    }
    else    
        puts("La RIceca a costo uniforme non è andata a buon fine.");
    
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
