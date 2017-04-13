#include <problem.h>



Problem* new_lake() {
    struct Problem* lake = (Problem*)calloc(1,sizeof(Problem));;
    lake->initial_state = new_lake_initial_state();
    lake->transition_functions = &lake_transition_functions; 
    lake->goal_test = &lake_goal_test;
    lake->constraint_test = &lake_constraint_test;//si puo togliere
    lake->print_state = &lake_print_state;
    lake->heuristic = &lake_heuristic;
    lake->step_cost = &lake_step_cost;
    lake->state_compare = &lake_state_compare;
    lake->depth_solution = LAKE_DLS_LIMIT;

    state_compare =  &lake_state_compare;
    return lake;
}


Problem* new_eight_puzzle(){
    srand(time(NULL));   
    struct Problem* eight_puzzle = (Problem*)calloc(1,sizeof(Problem));;
    eight_puzzle->initial_state = new_eight_puzzle_initial_state();
    eight_puzzle->transition_functions = &eight_puzzle_transition_functions; 
    eight_puzzle->goal_test = &eight_puzzle_goal_test;
    eight_puzzle->print_state = &eight_puzzle_print_state;
    eight_puzzle->heuristic = &eight_puzzle_heuristic;
    eight_puzzle->step_cost = &eight_puzzle_step_cost;
    eight_puzzle->state_compare = &eight_puzzle_state_compare;
    eight_puzzle->depth_solution = EIGHT_PUZZLE_DLS_LIMIT;

    state_compare =  &eight_puzzle_state_compare;
    return eight_puzzle;
}

