#define __EIGHT_PUZZLE__

#ifndef __COMMON__
	#include <common.h>
#endif
#include <time.h>
#include <stdlib.h>


#define EIGHT_PUZZLE_DLS_LIMIT 15
#define LEN_MATRIX ((COLUMN * ROW)-1)
#define COLUMN (3)
#define ROW  (3)  
#define BLANK 0 //definisce il numero considerato come cassella vuota

typedef State* (*Eight_puzzle_Action)(State*); 

typedef struct Eight_puzzle_state {
	int matrix[COLUMN][ROW];
	short int row_blank;
	short int column_blank;
} Eight_puzzle_state;



State* new_eight_puzzle_state();
State* new_eight_puzzle_initial_state();
Action* new_eight_puzzle_move(Eight_puzzle_Action moves);
List* eight_puzzle_transition_functions(State* generic_state);
Boolean eight_puzzle_goal_test(State* generic_state);
int eight_puzzle_step_cost(State* struct_state, int cost);
void eight_puzzle_print_state(State* generic_state);
void gen_matrix(struct Eight_puzzle_state* state);
struct Eight_puzzle_state* extract_state (State* generic_state);
void matriscopy (void* destmat, void* srcmat);
State* eight_puzzle_move_up(State* old_state);
State* eight_puzzle_move_right(State* old_state); 
State* eight_puzzle_move_down(State* old_state); 
State* eight_puzzle_move_left(State* old_state);
int eight_puzzle_heuristic(State* struct_state);
int eight_puzzle_state_compare(void* state1, void* state2);
int manhattan(int col, int row, int val);
Boolean isSolvable(State* state);

