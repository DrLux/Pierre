#define __NEWPROBLEM__

#ifndef __COMMON__
	#include <common.h>
#endif

#define NEWPROBLEM_DLS_LIMIT  0 //Il massimo livello nel quale la ricerca in profondita dovrà spingersi. Se non lo conosci lascia questo valore a 0

typedef State* (*Newproblem_Action)(State*); //Generica funzione che dato uno stato, restituisce il suo stato successore.

typedef struct newproblem_state {
	//Struttura dati che rappresenti tutti i possibili stati del problema
} Newproblem_state;


State* new_newproblem_state(); //Genera un nuovo stato del problema e lo incapsula dentro uno generico stato
State* new_newproblem_initial_state(); //Genera lo stato iniziale del problema e lo incapsula in uno generico stato
Action* new_newproblem_move(Newproblem_Action); //Incapsula un' azione del problema in una generica azione.

State* newproblem_move_possible(State* old_state); //Azione del problema che dato uno stato ne genera un successore.


List* newproblem_transition_functions(State* struct_state);//Dato uno stato, restituile la lista di tutte le possibili azioni del problema applicabili a quel determinato stato (rispettando i vincoli) 
Boolean newproblem_constraint_test(State* struct_state);//Restituisce true se lo stato rispetta i vincoli
Boolean newproblem_goal_test(State* struct_state);//Restituisce true se lo stato rispetta i vincoli ed è uno stato obiettivo
void newproblem_print_state(State* struct_state); 
int newproblem_heuristic(State* struct_state); //Stima il numero di passi rimaneneti da uno stato verso l' obiettivo. 
int newproblem_step_cost(State* struct_state, int cost); //Trova il costo di uno stato, a partire da quello del suo predecessore
int newproblem_state_compare(void* state1, void* state2); //Dati due stati, definisce la loro ugualianza


