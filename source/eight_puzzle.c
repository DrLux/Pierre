#include <eight_puzzle.h>

//Ammisibilità: http://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/
// Princeton: https://www.cs.princeton.edu/courses/archive/spr10/cos226/assignments/8puzzle.html
// relazioen http://www.marcomeoni.net/univ/ia/relazioneOTTO.pdf

/*
int main(){
	srand(time(NULL));   // should only be called once
	//struct State* puzzle = new_eight_puzzle_initial_state();
	//struct Action* moves = NULL;
	//int i = 0;
	//List* list = eight_puzzle_transition_functions(puzzle);

	while(!empty(list)){
		printf("Stato %d\n",i );
		moves = (Action*)pop_fifo(list);
		isSolvable(moves->move(puzzle));
	}

	for (int x = 0; x <100; x++)
		isSolvable(new_eight_puzzle_initial_state());

	return 0;
}
*/


State* new_eight_puzzle_state(){
	struct State* new_generic_state = new_state();
	struct Eight_puzzle_state* ep_root_state = (Eight_puzzle_state*)calloc(1,sizeof(Eight_puzzle_state));
	new_generic_state->state = (void*)ep_root_state;
	return new_generic_state;
}


State* new_eight_puzzle_initial_state(){
	struct State* new_generic_state = new_state();
	struct Eight_puzzle_state* ep_root_state = (Eight_puzzle_state*)calloc(1,sizeof(Eight_puzzle_state));
	gen_matrix(ep_root_state);
	new_generic_state->state = (void*)ep_root_state;
	return new_generic_state;
}

Action* new_eight_puzzle_move(Eight_puzzle_Action moves) {
    struct Action* actions = (Action*)calloc(1,sizeof(Action));    
	actions->move = moves;
    return actions;
}

List* eight_puzzle_transition_functions(State* generic_state){
	List* list = NULL;
	if (generic_state != NULL && generic_state->state != NULL){
		list = new_list();

			if (extract_state(generic_state)->column_blank == 0){
				push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_down));
			} else {
				if (extract_state(generic_state)->column_blank == 1){
					push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_up));
					push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_down));
				} else {
					if (extract_state(generic_state)->column_blank == 2){
						push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_up));
					}
				}
			}

			if (extract_state(generic_state)->row_blank == 0){
				push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_right));
			} else {
				if (extract_state(generic_state)->row_blank == 1){
					push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_right));
					push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_left));
				} else {
					if (extract_state(generic_state)->row_blank == 2){
						push(list,(void*)new_eight_puzzle_move(&eight_puzzle_move_left));						   		
					}
				}
			}
	}

	return list;
}

Boolean eight_puzzle_goal_test(State* generic_state){
	Boolean check = false;
	if (extract_state(generic_state)->column_blank == COLUMN-1 && extract_state(generic_state)->row_blank == ROW-1){         		  
		check = true;
		for (int i = 0; i < LEN_MATRIX && check; i++){
			check = extract_state(generic_state)->matrix[i/COLUMN][i%ROW] == i+1;
		}
	}
	return check;
}

int eight_puzzle_step_cost(State* struct_state, int cost){
	return cost+1; //problema di costo unitario
}

int eight_puzzle_heuristic(State* generic_state){
	int total = 0;
	for(int c = 0; c < COLUMN; c++)
		for (int r = 0; r < ROW; r++)
			if (extract_state(generic_state)->matrix[c][r] != (c*3+r+1))
				total += manhattan(c,r,extract_state(generic_state)->matrix[c][r]);
	return total;
}

int manhattan(int col, int row, int val){
	short int goal_c = (val-1)/COLUMN; //trova la vera colonna dove dovrebbe stare
	short int goal_r = (val-1)%ROW; //trova la vera riga dove dovrebbe stare

	if (val == BLANK){ //il blank va diretto alla fine senza calcoli
		goal_c = COLUMN-1;
		goal_r = ROW-1;
	}

	return (abs(goal_c - col) + abs(goal_r - row) );
}

void eight_puzzle_print_state(State* generic_state){
	if (generic_state != NULL && generic_state->state != NULL){
		if (eight_puzzle_goal_test(generic_state))
			puts("Stato Vincente");

		puts("\n-------------");
		for (int y = 0; y <= 2; y++){
			printf("|");
			for (int x = 0; x <= 2; x++){
				//if x != state->blank
				if (extract_state(generic_state)->matrix[y][x] != BLANK)	
					printf(" %d ", extract_state(generic_state)->matrix[y][x]);
				else
					printf("   ");
				printf("|");
			}
			puts("\n----+---+----");
		}
	puts("");
	}
}


void gen_matrix(struct Eight_puzzle_state* state){
	/*int mtx[COLUMN][ROW] = {{7, 2, 4},
    		                {5, 0, 6},  // Value 0 is used for empty space
            		        {8, 3, 1}};
    */

    int temp_array[LEN_MATRIX+1] = { -1, -1,-1, -1,-1, -1,-1, -1, -1 };
    int mtx[COLUMN][ROW];
    int numrand = 0;

    for (int c = 0; c < COLUMN; c++){
    	for (int r = 0; r < ROW; r++){
    		numrand = rand()%(LEN_MATRIX+1); 
    		if(temp_array[numrand] == -1){
    			temp_array[numrand] = numrand;
    			mtx[c][r] = numrand;
    		} else {
    			r--;
    		}
    	}
    }


    for (int i = 0; i<= LEN_MATRIX; i++){
		state->matrix[i/COLUMN][i%ROW] = mtx[i/COLUMN][i%ROW];
		if ( mtx[i/COLUMN][i%ROW] == 0){
			state->column_blank = i/COLUMN;
			state->row_blank = i%ROW;
		}
	} 

}


struct Eight_puzzle_state* extract_state (State* generic_state){
	struct Eight_puzzle_state* struct_state = (struct Eight_puzzle_state*)generic_state->state;
	return struct_state;
}

void matriscopy (void* destmat, void* srcmat) {
  memcpy(destmat,srcmat, ROW*COLUMN*sizeof(int));
}

State* eight_puzzle_move_up(State* old_state){
	struct State* new_generic_state = new_eight_puzzle_state();
	matriscopy((void*)extract_state(new_generic_state),(void*)extract_state(old_state) );

	int c = extract_state(old_state)->column_blank;
	int r = extract_state(old_state)->row_blank;

	extract_state(new_generic_state)->matrix[c][r] = extract_state(new_generic_state)->matrix[c-1][r]; 
	extract_state(new_generic_state)->matrix[c-1][r] = BLANK;

	extract_state(new_generic_state)->column_blank = c-1;
	extract_state(new_generic_state)->row_blank = r;

	return new_generic_state;
}



State* eight_puzzle_move_right(State* old_state){
	struct State* new_generic_state = new_eight_puzzle_state();
	matriscopy((void*)extract_state(new_generic_state),(void*)extract_state(old_state) );

	int c = extract_state(old_state)->column_blank;
	int r = extract_state(old_state)->row_blank;

	extract_state(new_generic_state)->matrix[c][r] = extract_state(new_generic_state)->matrix[c][r+1]; 
	extract_state(new_generic_state)->matrix[c][r+1] = BLANK;

	extract_state(new_generic_state)->column_blank = c;
	extract_state(new_generic_state)->row_blank = r+1;

	return new_generic_state;
}

State* eight_puzzle_move_down(State* old_state){
	struct State* new_generic_state = new_eight_puzzle_state();
	matriscopy((void*)extract_state(new_generic_state),(void*)extract_state(old_state) );

	int c = extract_state(old_state)->column_blank;
	int r = extract_state(old_state)->row_blank;

	extract_state(new_generic_state)->matrix[c][r] = extract_state(new_generic_state)->matrix[c+1][r]; 
	extract_state(new_generic_state)->matrix[c+1][r] = BLANK;

	extract_state(new_generic_state)->column_blank = c+1;
	extract_state(new_generic_state)->row_blank = r;

	return new_generic_state;
}


State* eight_puzzle_move_left(State* old_state){
	struct State* new_generic_state = new_eight_puzzle_state();
	matriscopy((void*)extract_state(new_generic_state),(void*)extract_state(old_state) );

	int c = extract_state(old_state)->column_blank;
	int r = extract_state(old_state)->row_blank;

	extract_state(new_generic_state)->matrix[c][r] = extract_state(new_generic_state)->matrix[c][r-1]; 
	extract_state(new_generic_state)->matrix[c][r-1] = BLANK;

	extract_state(new_generic_state)->column_blank = c;
	extract_state(new_generic_state)->row_blank = r-1;

	return new_generic_state;
}

//torna 0/false se sono uguali, 1/vero altrimenti
int eight_puzzle_state_compare(void* state1, void* state2){
	int ret = false;
	if (state1 != NULL && state2 != NULL){
		struct Eight_puzzle_state* st1 = extract_state((State*)state1);
		struct Eight_puzzle_state* st2 = extract_state((State*)state2);
		ret = true;         		  
		for (int i = 0; i<= LEN_MATRIX && ret; i++)
			ret = st1->matrix[i/COLUMN][i%ROW] == st2->matrix[i/COLUMN][i%ROW];	
	}
    return !ret;
}

//torna 1 quando è true
Boolean isSolvable(State* state){
	int count = 1;
    for (int c = 0; c < COLUMN; c++)
        for (int r = 1; r < ROW; r++)
             if (extract_state(state)->matrix[c][r-1] > extract_state(state)->matrix[c][r])
                  count++;

    printf("Risoluzione: %d\n", count%2);
    eight_puzzle_print_state(state);
    return (count % 2);
}

