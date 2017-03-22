#define __LAKE__

#ifndef __LIST__
	#include <list.h>
#endif

#define Boolean int
#define true 1
#define false 0

#define NUM_ACTIONS_LAKE  4
#define NUM_VARIABLE_LAKE  4

int transition_functions(List* list, void* state);//riempie la lista con le mosse ammissibili e ne ritorna il numero
Boolean constraint_test(void* state);//torna true se rispetta i vincoli
Boolean goal_test(void* state);//torna true se rispetta i vincoli ed è uno stato obiettivo
void print_state(void* state);
void print_solution(List* list);
int heuristic(void* state);
int step_cost(void* state, int cost);


// 0 = Uomo, 1 = Cavolo, 2 = Pecola, 3 = Lupo
typedef struct Lake {
	int initial_state[NUM_VARIABLE_LAKE];
	int (*transition_functions)(List* list, void* state);
	int (*goal_test)(void* state);
	int (*constraint_test)(void* state);
	void (*print_state)(void* state);
	void (*print_solution)(List* list);
	int (*heuristic)(void* state);
	int (*step_cost)(void* state, int cost);
} Lake;

Lake* new_lake();

void move_man(void* old_state, void* new_state);
void move_man_cabbage(void* old_state, void* new_state);
void move_man_sheep(void* old_state, void* new_state);
void move_man_wolf(void* old_state, void* new_state);
