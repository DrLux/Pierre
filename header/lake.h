#define __LAKE__

#ifndef __COMMON__
	#include <common.h>
#endif

#define LAKE_DLS_LIMIT  7
#define NUM_ACTIONS_LAKE  4
#define NUM_VARIABLE_LAKE  4

typedef struct Lake_state {
	Boolean state[NUM_VARIABLE_LAKE];
} Lake_state;


State* new_lake_state();
//serve per astrarre dallo stato. solo il problema sa come riempire questa struct
State* new_lake_initial_state();
//unico costruttore che modifica la mossa nella struct che genera, in base all' indice passato come parametro
Action* new_lake_move(int move_index);

State* lake_move_man(State* old_state);
State* lake_move_man_cabbage(State* old_state);
State* lake_move_man_sheep(State* old_state);
State* lake_move_man_wolf(State* old_state);

List* lake_transition_functions(State* struct_state);//riempie la lista con le mosse ammissibili(ogni mossa una struct) 
Boolean lake_constraint_test(State* struct_state);//torna true se rispetta i vincoli
Boolean lake_goal_test(State* struct_state);//torna true se rispetta i vincoli ed è uno stato obiettivo
void lake_print_state(State* struct_state);
int lake_heuristic(State* struct_state);
int lake_step_cost(State* struct_state, int cost);
int lake_state_compare(void* state1, void* state2);
Lake_state* extract_lake_state (State* generic_state);

