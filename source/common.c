#include "common.h"

long int states = 0;

State* new_state(){
    struct State* new_state = (State*)calloc(1,sizeof(State));
    new_state->state = NULL;
    new_state->id = states++;
    return new_state;
}


long int get_num_states(){
	return states;
}