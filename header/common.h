#define __COMMON__

#ifndef __LIST__
	#include <list.h>
#endif
#include <stdio.h>
#include <string.h> //per il memcpy

#define Boolean int
#define true 1
#define false 0

typedef struct State {
	long int id; 
	void* state;
} State;

typedef struct Action {
	State* (*move)(State* old_state);
} Action;

//genera un generico stato, incrementandone l' id
State* new_state();

long int get_num_states();

void swap(void* pt1, void* pt2);
void state_reset_count();