#include "common.h"

long int id_states = 0;

State* new_state(){
    struct State* new_state = (State*)calloc(1,sizeof(State));
    new_state->state = NULL;
    new_state->id = id_states++;
    return new_state;
}


long int get_num_states(){
	return id_states;
}

void state_reset_count(){
    id_states = 0;
}

void swap(void* pt1, void* pt2){
	void* temp = pt1;
	pt1 = pt2;
	pt2 = temp;
}