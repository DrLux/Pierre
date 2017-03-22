#define __LAKE__

#ifndef __LIST__
	#include <list.h>
#endif

#define Boolean int
#define true 1
#define false 0

#define NUM_ACTIONS_LAKE  4
#define NUM_VARIABLE_LAKE  4

void transition_functions(List* list, void* state);//riempie la lista con le mosse ammissibili(ogni mossa una struct) 
Boolean constraint_test(void* state);//torna true se rispetta i vincoli
Boolean goal_test(void* state);//torna true se rispetta i vincoli ed è uno stato obiettivo
void print_state(void* state);
void print_solution(List* list);
int heuristic(void* state);
int step_cost(void* state, int cost);

//azioni possibili
void move_man(void* old_state, void* new_state);
void move_man_cabbage(void* old_state, void* new_state);
void move_man_sheep(void* old_state, void* new_state);
void move_man_wolf(void* old_state, void* new_state);

// 0 = Uomo, 1 = Cavolo, 2 = Pecola, 3 = Lupo
typedef struct Lake {
	int initial_state[NUM_VARIABLE_LAKE];
	void (*transition_functions)(List* list, void* state);
	int (*goal_test)(void* state);
	int (*constraint_test)(void* state);
	void (*print_state)(void* state);
	void (*print_solution)(List* list);
	int (*heuristic)(void* state);
	int (*step_cost)(void* state, int cost);
} Lake;

//struct universale per tutte le mosse del prolema.
typedef struct lake_move {
	void (*move)(void* old_state, void* new_state);
} lake_move;

Lake* new_lake();
//unico costruttore che modifica la mossa nella struct che genera, in base all' indice passato come parametro
lake_move* new_lake_move(int move_index);