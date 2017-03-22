#include <lake.h>

/*todo: trovare un modo più efficente per fare questo
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
*/

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

lake_move* new_lake_move(int move_index) {
    struct lake_move* action = (lake_move*)calloc(1,sizeof(lake_move));
    switch (move_index) {
			case 0:
				action->move = &move_man;
				break; 
			case 1:
				action->move = &move_man_cabbage;
				break; 
			case 2:
				action->move = &move_man_sheep;
				break; 
			case 3:
				action->move = &move_man_wolf;
				break; 
			default:
			   printf("Print nella default di new_lake_move");
			   break;
			}
    
    return action;
}


void transition_functions(List* list, void* state){
	if (state != NULL){

		Boolean* actual_state = (Boolean*)state;
		Boolean temp_state[NUM_VARIABLE_LAKE];

		for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
	    	if (actual_state[i] == actual_state[0]){ //solo gli attori sulla stessa sponda del' uomo possono attraversare il fiume con lui
	    		switch (i) {
				case 0:
					move_man((void*)actual_state, (void*)&temp_state);
					break; 
				case 1:
					move_man_cabbage((void*)actual_state, (void*)&temp_state);			   
					break; 
			    case 2:
					move_man_sheep((void*)actual_state, (void*)&temp_state);
					break; 
				case 3:
					move_man_wolf((void*)actual_state, (void*)&temp_state);
					break; 
				default:
					printf("Print nella default di transiction_functions");
					break;
				}

				if (constraint_test((void*)temp_state))	//dopo aver generato una possibile azione vedo se rispetta i vincoli
			   			push(list,(void*)new_lake_move(i));		   		
			} 
		}
	}
}

//torna true se rispetta i vincoli
int constraint_test(void* state){
	if (state == NULL)
		return false;
	Boolean* actual_state = (Boolean*)state;
	Boolean ret = true;
	if ((actual_state[0] != actual_state[1]) && (actual_state[1] == actual_state[2])) //se non sono nella stessa sponda dell' uomo vengono mangiati
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

int heuristic(void* state){
	return 1; //per ora non viene usata
}

int step_cost(void* state, int cost){
	return cost+1; //problema di costo unitario
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
    new[0] = !new[0];
	new[1] = !new[1];
}

void move_man_sheep(void* old_state, void* new_state){
	Boolean* old = (Boolean*)old_state;
	Boolean* new = (Boolean*)new_state;
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
    }
    new[0] = !new[0];
	new[2] = !new[2];
}

void move_man_wolf(void* old_state, void* new_state){
	Boolean* old = (Boolean*)old_state;
	Boolean* new = (Boolean*)new_state;
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
    }
    new[0] = !new[0];
	new[3] = !new[3];
}


/*int main(){
    struct Lake* problem = new_lake();
    List* list = new_list();
    struct lake_move* temp_move = NULL;
    Boolean temp_state[NUM_VARIABLE_LAKE];


    problem->transition_functions(list,problem->initial_state);

    temp_move = pop_fifo(list);
    while (temp_move != NULL){
    	temp_move->move(problem->initial_state,(void*)&temp_state);
    	problem->print_state((void*)&temp_state);
    	temp_move = pop_fifo(list);
    }

    return 0;
}
*/