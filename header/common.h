#define __COMMON__

typedef struct State {
	void* state;
} State;

//equivalente di lake_move. Solo per una questione di non usare la parola lake, ma le posso equicastare
typedef struct Action {
	State* (*move)(State* old_state);
} Action;