#define __PROBLEM__

#ifndef __LAKE__
	#include <lake.h>
#endif

// 0 = Uomo, 1 = Cavolo, 2 = Pecola, 3 = Lupo
//aggiungere a problem anche il new_state. Nel costruttore del problema scelgo quale se usare lake_new_state o altri
typedef struct Problem {
	State* initial_state; //è un attributo
	State* (*new_state)(); //funzione che genera un nuovo stato inizializzato(a questo livello di astrazione non so cosa è uno stato )
	List* (*transition_functions)(State* state);
	Boolean (*goal_test)(State* state);
	Boolean (*constraint_test)(State* state);
	void (*print_state)(State* state);
	void (*print_solution)(List* list);//potenzialmente inutile
	int (*heuristic)(State* state);
	int (*step_cost)(State* state, int cost);
	int (*state_compare)(void* state1, void* state2);
} Problem;



//genera la struct che contiene tutte le informazioni del problema
Problem* new_lake();

