#include <lake.h>

//todo: astrarre lo stato con una struct

#define Boolean int
#define true 1
#define false 0

#define NUM_ACTIONS_LAKE  4
#define NUM_VARIABLE_LAKE  4

int transition_functions(List* list, void* state){
	return 0;
}


//torna true se rispetta i vincoli
int constraint_test(void* state){
	Boolean* actual_state = (Boolean*)state;
	Boolean ret = true;
	if ((actual_state[0] != actual_state[1]) && (actual_state[1] == actual_state[2]))
		ret = false;
	if ((actual_state[0] != actual_state[2]) && (actual_state[2] == actual_state[3]))
		ret = false;
	return ret;
}

int goal_test(void* state){
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

typedef struct lake {
	//actions[]; array di funzioni
	int initial_state[NUM_VARIABLE_LAKE];
	int (*transition_functions)(List* list, void* state);
	int (*goal_test)(void* state);
	int (*constraint_test)(void* state);
	void (*print_state)(void* state);
	void (*print_solution)(List* list);
	int (*heuristic)(void* state);
	int (*step_cost)(void* state, int cost);
} lake;





lake new_lake() {
    struct lake problem;

    for (int i = 0; i < NUM_VARIABLE_LAKE; i++)
    	problem.initial_state[i] = false;

    problem.transition_functions = &transition_functions;
    problem.goal_test = &goal_test;
    problem.constraint_test = &constraint_test;
    problem.print_state = &print_state;
    problem.print_solution = &print_solution;
    problem.heuristic = &heuristic;
    problem.step_cost = &step_cost;
    return problem;
}

int main(){
    struct lake problem = new_lake();
    List* list = new_list();
    int state1[NUM_VARIABLE_LAKE];
    int state2[NUM_VARIABLE_LAKE];
    int state3[NUM_VARIABLE_LAKE];
    int state4[NUM_VARIABLE_LAKE];
    int state5[NUM_VARIABLE_LAKE];

    for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	state1[i] = false;
    	state2[i] = false;
    	state3[i] = false;
    	state4[i] = true;
    	state5[i] = true;
    }

    state2[0] = true;


    state3[0] = true;
    state3[1] = true;

    state4[3] = false;
    

    push(list,(void*)&state1);
    push(list,(void*)&state2);
    push(list,(void*)&state3);
    push(list,(void*)&state4);
    push(list,(void*)&state5);
    
   

    problem.print_solution(list);

    return 0;
} 

