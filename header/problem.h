#define __PROBLEM__

#ifndef __LAKE__
	#include <lake.h>
#endif

#ifndef __EIGHT_PUZZLE__
	#include <eight_puzzle.h>
#endif

// 0 = Uomo, 1 = Cavolo, 2 = Pecola, 3 = Lupo
//aggiungere a problem anche il new_state. Nel costruttore del problema scelgo quale se usare lake_new_state o altri
typedef struct Problem {
	State* initial_state; //è un attributo
	long int depth_solution;
	List* (*transition_functions)(State* state);
	Boolean (*goal_test)(State* state);
	Boolean (*constraint_test)(State* state);
	void (*print_state)(State* state);
	int (*heuristic)(State* state);
	int (*step_cost)(State* state, int cost);
	int (*state_compare)(void* state1, void* state2);
} Problem;

//genera la struct che contiene tutte le informazioni del problema
Problem* new_lake();

Problem* new_eight_puzzle();

