#include <problem.h>

Problem* new_lake() {
    struct Problem* lake = (Problem*)calloc(1,sizeof(Problem));;
    lake->initial_state = new_lake_initial_state();
    lake->new_state = &new_lake_state;
    lake->transition_functions = &lake_transition_functions;
    lake->goal_test = &lake_goal_test;
    lake->constraint_test = &lake_constraint_test;
    lake->print_state = &lake_print_state;
    lake->print_solution = &lake_print_solution;
    lake->heuristic = &lake_heuristic;
    lake->step_cost = &lake_step_cost;
    lake->state_compare = &lake_state_compare;
    return lake;
}

