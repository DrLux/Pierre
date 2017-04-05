#define __LIST__

#include <stdlib.h>
#include <stdio.h>

//Struttura che rappresenta il nodo di una lista
typedef struct l_node{
	void* cargo;
	struct l_node* next;
} List_Node;

//Struttura che rappresenta la lista (Tipologia con sentinella)
typedef struct {
	int size;
	List_Node* sentinel;
} List;

//torna 0 se i due elementi (probabilmete stati) sono uguali, 1 se il primo è maggiore, -1 altrimenti
typedef int (*EqualsFunction)(void*, void*);

List* new_list();
List_Node* create_node(void* ptr);
//Inserisci in testa
void push(List* list,void* ptr);
//rimuove in testa
void* pop_lifo(List* list);
//rimuove in coda
void* pop_fifo(List* list);
//restituisce TRUE se la lista è vuota
int empty(List* list);
int size(List* list);
void clean_list(List* list);

//torna true se sono uguali 
int is_present(List* list, void* ptr, EqualsFunction equals);