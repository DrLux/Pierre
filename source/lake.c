#include <lake.h>

/*todo: trovare un modo più efficente per fare questo
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new[i] = old[i];
*/

//creo l' array e lo inizializzo
State* new_lake_state(){
	struct State* new_generic_state = new_state();
	struct Lake_state* lake_state = (Lake_state*)calloc(1,sizeof(Lake_state));
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++)
		lake_state->state[i] = -1;
	new_generic_state->state = (void*)lake_state;
	return new_generic_state;
}

//dovrei fare una super ma non voglio inizializzare a 0 e poi rinizializzare a false
State* new_lake_initial_state(){
	struct State* new_generic_state = new_state();
	struct Lake_state* lake_root_state = (Lake_state*)calloc(1,sizeof(Lake_state));
	for (int i = 0; i < NUM_VARIABLE_LAKE; i++)
		lake_root_state->state[i] = false;
	new_generic_state->state = (void*)lake_root_state;
	return new_generic_state;
}



Action* new_lake_move(int move_index) {
    struct Action* actions = (Action*)calloc(1,sizeof(Action));
    switch (move_index) {
			case 0:
				actions->move = &lake_move_man;
				break; 
			case 1:
				actions->move = &lake_move_man_cabbage;
				break; 
			case 2:
				actions->move = &lake_move_man_sheep;
				break; 
			case 3:
				actions->move = &lake_move_man_wolf;
				break; 
			default:
			   printf("Print nella default di new_lake_move");
			   break;
			}
    
    return actions;
}


List* lake_transition_functions(State* generic_state){
	List* list = NULL;
	if (generic_state != NULL && generic_state->state != NULL){
		list = new_list();
		State* temp_state = NULL;

		for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
	    	if (extract_lake_state(generic_state)->state[i] == extract_lake_state(generic_state)->state[0]){ //solo gli attori sulla stessa sponda del' uomo possono attraversare il fiume con lui
	    		switch (i) {
				case 0:
					temp_state = lake_move_man(generic_state);
					break; 
				case 1:
					temp_state = lake_move_man_cabbage(generic_state);			   
					break; 
			    case 2:
					temp_state = lake_move_man_sheep(generic_state);
					break; 
				case 3:
					temp_state = lake_move_man_wolf(generic_state);
					break; 
				default:
					printf("Print nella default di transiction_functions");
					break;
				}

				if (lake_constraint_test(temp_state))	//dopo aver generato una possibile azione vedo se rispetta i vincoli
			   			push(list,(void*)new_lake_move(i));
			} 
		}		   		
	}
	return list;
}

//torna true se rispetta i vincoli
Boolean lake_constraint_test(State* struct_state){
	if (struct_state == NULL || struct_state->state == NULL)
		return false;
	Boolean* actual_state = extract_lake_state(struct_state)->state;
	Boolean ret = true;
	if ((actual_state[0] != actual_state[1]) && (actual_state[1] == actual_state[2])) //se non sono nella stessa sponda dell' uomo vengono mangiati
		ret = false;
	if ((actual_state[0] != actual_state[2]) && (actual_state[2] == actual_state[3]))
		ret = false;
	return ret;
}

Boolean lake_goal_test(State* struct_state){
	if (struct_state == NULL || struct_state->state == NULL)
		return false;
	Boolean ret = lake_constraint_test(struct_state); //se non rispetta i vincoli esco subito dai controlli
		for (int i = 0; i < NUM_VARIABLE_LAKE && ret; i++)
			ret = extract_lake_state(struct_state)->state[i]; //appena c'è una variabile false esco dal ciclo
	return ret;
}

int lake_heuristic(State* struct_state){
	return 1; //per ora non viene usata
}

int lake_step_cost(State* struct_state, int cost){
	return cost+1; //problema di costo unitario
}

void lake_print_state(State* struct_state){
	if (struct_state != NULL && struct_state->state != NULL){
	
		char coast = ' ';
		if (!lake_constraint_test(struct_state))
			puts("(Stato non ammissibile)");

		if (lake_goal_test(struct_state))
			puts("(Stato Goal!)");
		for (int i = 0; i < NUM_VARIABLE_LAKE; i++){


			if (extract_lake_state(struct_state)->state[i] == true)
				coast = 'B';
			else
				coast = 'A';

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
}

//prende uno lake_state come parametro ma torna uno State normale
State* lake_move_man(State* old_state){
	struct State* new_generic_state = new_lake_state();
	Lake_state* new = extract_lake_state(new_generic_state);

	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new->state[i] = extract_lake_state(old_state)->state[i];
    }

	new->state[0] = !new->state[0];
	new_generic_state->state = (void*)new;
	return new_generic_state;
}

State* lake_move_man_cabbage(State* old_state){
	struct State* new_generic_state = new_lake_state();
	Lake_state* new = extract_lake_state(new_generic_state);

	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new->state[i] = extract_lake_state(old_state)->state[i];
    }
    new->state[0] = !new->state[0];
	new->state[1] = !new->state[1];
	new_generic_state->state = (void*)new;
	return new_generic_state;
}

State* lake_move_man_sheep(State* old_state){
	struct State* new_generic_state = new_lake_state();
	Lake_state* new = extract_lake_state(new_generic_state);

	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new->state[i] = extract_lake_state(old_state)->state[i];
    }
    new->state[0] = !new->state[0];
	new->state[2] = !new->state[2];

	new_generic_state->state = (void*)new;
	return new_generic_state;
}

State* lake_move_man_wolf(State* old_state){
	struct State* new_generic_state = new_lake_state();
	Lake_state* new = extract_lake_state(new_generic_state);

	for (int i = 0; i < NUM_VARIABLE_LAKE; i++){
    	new->state[i] = extract_lake_state(old_state)->state[i];
    }
    new->state[0] = !new->state[0];
	new->state[3] = !new->state[3];

	new_generic_state->state = (void*)new;
	return new_generic_state;
}

//extact lake state from a generic state
Lake_state* extract_lake_state (State* generic_state){
	Lake_state* struct_state = (Lake_state*)generic_state->state;
	return struct_state;
}

//torna 0 se sono uguali, 1 altrimenti
int lake_state_compare(void* state1, void* state2){

	int ret = false;
	if (state1 != NULL && state2 != NULL){
		Lake_state* st1 = extract_lake_state((State*)state1);
		Lake_state* st2 = extract_lake_state((State*)state2);
		ret = true;
		for (int i = 0; i < NUM_VARIABLE_LAKE && ret; i++){
			if (st1 == NULL)
	    	ret = (st1->state[i] == st2->state[i]);
	    }
	}
    return !ret;
}