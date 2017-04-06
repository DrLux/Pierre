#include <problem.h>

Problem* new_lake() {
    struct Problem* lake = (Problem*)calloc(1,sizeof(Problem));;
    lake->initial_state = new_lake_initial_state();
    lake->new_state = &new_lake_state; //questa a quanto pare non serve
    lake->transition_functions = &lake_transition_functions;
    lake->goal_test = &lake_goal_test;
    lake->constraint_test = &lake_constraint_test;
    lake->print_state = &lake_print_state;
    lake->heuristic = &lake_heuristic;
    lake->step_cost = &lake_step_cost;
    lake->state_compare = &lake_state_compare;
    lake->depth_solution = LAKE_DLS_LIMIT;
    return lake;
}

