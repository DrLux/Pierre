#include <lake.h>

//todo: astrarre lo stato con una struct

int transition_functions(List* list, void* state){
	if (state == NULL)
		return 0;

	Boolean* actual_state = (Boolean*)state;
	Boolean temp_state[NUM_VARIABLE_LAKE];
	int legal_moves = 0;

	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	if (actual_state[i] == actual_state[0]){
    		switch (i) {
			case 0:
			   	move_man((void*)actual_state, (void*)&temp_state);
			   	if (constraint_test((void*)temp_state)){		
		   			push(list,(void*)&move_man);
		   			legal_moves++;
		   		}
			   break; 
			case 1:
			   move_man_cabbage((void*)actual_state, (void*)&temp_state);
			   if (constraint_test((void*)temp_state)){		
		   			push(list,(void*)&move_man_cabbage);
		   			legal_moves++;
		   		}
			   break; 
		   case 2:
			   move_man_sheep((void*)actual_state, (void*)&temp_state);
			   if (constraint_test((void*)temp_state)){		
		   			push(list,(void*)&move_man_sheep);
		   			legal_moves++;
		   		}
			   break; 
			case 3:
			   move_man_wolf((void*)actual_state, (void*)&temp_state);
			   if (constraint_test((void*)temp_state)){		
		   			push(list,(void*)&move_man_wolf);
		   			legal_moves++;
		   		}
			   break; 
			default:
			   printf("Print nella default di transiction_functions");
			   break;
			}
		} 
    }
	return legal_moves;
}


//metodo costruttore
Lake* new_lake() {
    struct Lake* problem = (Lake*)calloc(1,sizeof(Lake));;

    for (int i = 0; i < NUM_VARIABLE_LAKE; i++)
    	problem->initial_state[i] = false;

    problem->transition_functions = &transition_functions;
    problem->goal_test = &goal_test;
    problem->constraint_test = &constraint_test;
    problem->print_state = &print_state;
    problem->print_solution = &print_solution;
    problem->heuristic = &heuristic;
    problem->step_cost = &step_cost;
    return problem;
}



//torna true se rispetta i vincoli
int constraint_test(void* state){
	if (state == NULL)
		return false;
	Boolean* actual_state = (Boolean*)state;
	Boolean ret = true;
	if ((actual_state[0] != actual_state[1]) && (actual_state[1] == actual_state[2]))
		ret = false;
	if ((actual_state[0] != actual_state[2]) && (actual_state[2] == actual_state[3]))
		ret = false;
	return ret;
}

int goal_test(void* state){
	if (state == NULL)
		return false;
	Boolean* actual_state = (Boolean*)state;
	Boolean ret = constraint_test(state); //se non rispetta i vincoli esco subito dai controlli
		for (int i = 0; i < NUM_VARIABLE_LAKE && ret; i++)
			ret = actual_state[i]; //appena c'è una variabile false esco dal ciclo
	return ret;
}

void print_state(void* state){
	Boolean* actual_state = (Boolean*)state;
	char coast = ' ';
	if (!constraint_test(state))
		puts("(Stato non ammissibile)");

	if (goal_test(state))
		puts("(Stato Goal!)");
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){


		if (actual_state[i] == true)
			coast = 'b';
		else
			coast = 'a';

		switch (i) {
			case 0:
			   printf("L' uomo è sulla costa: %c\n", coast);
			   break; 
			case 1:
			   printf("Il cavolo è sulla costa: %c\n", coast);
			   break; 
		   case 2:
			   printf("La pecora è sulla costa: %c\n", coast);
			   break; 
			case 3:
			   printf("Il lupo è sulla costa: %c\n\n", coast);
			   break; 
			default:
			   printf("Print nella default di print_state");
			   break;
		}
	}
}

void print_solution(List* list){
	int num_state = 0;
	printf("\n\t ** Soluzione ** \n");
	void* actual_state = pop_fifo(list);
	while (actual_state != NULL){
		printf("\n\t ** State N. %d ** \n", num_state++);
		print_state(actual_state);
		actual_state = pop_fifo(list);
	}
	
}

int heuristic(void* state){
	return 1;
}

int step_cost(void* state, int cost){
	return cost+1;
}



void move_man(void* old_state, void* new_state){
	Boolean* old = (Boolean*)old_state;
	Boolean* new = (Boolean*)new_state;
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
    }
	new[0] = !new[0];
}

void move_man_cabbage(void* old_state, void* new_state){
	Boolean* old = (Boolean*)old_state;
	Boolean* new = (Boolean*)new_state;
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
    }
	new[1] = !new[1];
}

void move_man_sheep(void* old_state, void* new_state){
	Boolean* old = (Boolean*)old_state;
	Boolean* new = (Boolean*)new_state;
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
    }
	new[2] = !new[2];
}

void move_man_wolf(void* old_state, void* new_state){
	Boolean* old = (Boolean*)old_state;
	Boolean* new = (Boolean*)new_state;
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
    }
	new[3] = !new[3];
}


int main(){
    struct Lake* problem = new_lake();
    List* list = new_list();

    problem->transition_functions(list,problem->initial_state);

    problem->print_solution(list);

    return 0;
} 
