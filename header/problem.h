#define __PROBLEM__

#ifndef __LAKE__
	#include <lake.h>
#endif

#ifndef __EIGHT_PUZZLE__
	#include <eight_puzzle.h>
#endif
//variabile globale che permette di confrontare due NODE secondo i loro stati.La inizializzo nelle new
int (*state_compare)(void* state1, void* state2); 

typedef struct Problem {
	State* initial_state; 
	long int depth_solution;
	List* (*transition_functions)(State* state);
	Boolean (*goal_test)(State* state);
	void (*print_state)(State* state);
	int (*heuristic)(State* state);
	int (*step_cost)(State* state, int cost);
	int (*state_compare)(void* state1, void* state2);
} Problem;

Problem* new_lake();

Problem* new_eight_puzzle();



