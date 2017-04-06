#include <eight_puzzle.h>

//Ammisibilità: http://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/
// Princeton: https://www.cs.princeton.edu/courses/archive/spr10/cos226/assignments/8puzzle.html

int main(){
	eight_puzzle_initial_state();
	return 0;
}

void eight_puzzle_initial_state(){
	//struct State* new_generic_state = new_state();
	struct Eight_puzzle_state* ep_root_state = (Eight_puzzle_state*)calloc(1,sizeof(Eight_puzzle_state));
	gen_matrix(ep_root_state);
	eight_puzzle_print_state(ep_root_state);
	//new_generic_state->state = (void*)ep_root_state;
	//return new_generic_state;
}

//void eight_puzzle_print_state(State* struct_state){
void eight_puzzle_print_state(struct Eight_puzzle_state* state){
	if (state != NULL && state->matrix != NULL){
		puts("\n-------------");
		for (int y = 0; y <= 2; y++){
			printf("|");
			for (int x = 0; x <= 2; x++){
				if (state->matrix[y][x] != 0)	
					printf(" %d ", state->matrix[y][x]);
				else
					printf("   ");
				printf("|");
			}
			puts("\n----+---+----");
		}
	puts("");
	}
}

Boolean eight_puzzle_goal_test(struct Eight_puzzle_state* state){
	Boolean check = true;         		  
	for (int i = 0; i<= LEN_MATRIX && check; i++){
		check = state->matrix[i/COLUMN][i%ROW] == i;
	}
	return check;
}

void gen_matrix(struct Eight_puzzle_state* state){
	int mtx[COLUMN][ROW] = {{1, 8, 2},
    		                {0, 4, 3},  // Value 0 is used for empty space
            		        {7, 6, 5}};

    for (int i = 0; i<= LEN_MATRIX; i++){
		state->matrix[i/COLUMN][i%ROW] = mtx[i/COLUMN][i%ROW];
	}        		      
}