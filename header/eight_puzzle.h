#define __EIGHT_PUZZLE__

#ifndef __COMMON__
	#include <common.h>
#endif

#define EIGHT_PUZZLE_DLS_LIMIT  0 
#define LEN_MATRIX ((COLUMN * ROW)-1)
#define COLUMN (3)
#define ROW  (3)  

typedef State* (*Eight_puzzle_Action)(State*); 

typedef struct Eight_puzzle_state {
	int matrix[COLUMN][ROW];
} Eight_puzzle_state;


State* eight_puzzle_state(); 
Action* eight_puzzle_move(Eight_puzzle_Action); 

State* eight_puzzle_move_up(State* old_state); 
State* eight_puzzle_move_right(State* old_state); 
State* eight_puzzle_move_down(State* old_state); 
State* eight_puzzle_move_left(State* old_state); 


List* eight_puzzle_transition_functions(State* struct_state);
Boolean eight_puzzle_constraint_test(State* struct_state);
int eight_puzzle_heuristic(State* struct_state); 
int eight_puzzle_step_cost(State* struct_state, int cost);
int eight_puzzle_state_compare(void* state1, void* state2); 



void eight_puzzle_initial_state(); 
void gen_matrix(struct Eight_puzzle_state* state);
void eight_puzzle_print_state(struct Eight_puzzle_state* state); 
Boolean eight_puzzle_goal_test(struct Eight_puzzle_state* state);
