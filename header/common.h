#define __COMMON__

#define Boolean int
#define true 1
#define false 0

typedef struct State {
	long int id;
	void* state;
} State;

//equivalente di lake_move. Solo per una questione di non usare la parola lake, ma le posso equicastare
typedef struct Action {
	State* (*move)(State* old_state);
} Action;