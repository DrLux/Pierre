#include <stdio.h>
#include <stdlib.h>


typedef struct {
    long int priority; //a priorità crescente
    void* data;
} pr_node;
 
typedef struct {
    pr_node* nodes;
    int len; //conta gli elementi presenti
    int size;
} pr_heap;

//torna 0 se i due elementi (probabilmete stati) sono uguali, 1 se il primo è maggiore, -1 altrimenti
typedef int (*PREqualsFunction)(void*, void*);

void pr_push (pr_heap* h, long int priority, void* data);
void* pr_pop (pr_heap* h);
int pr_empty(pr_heap* h);//restituisce TRUE se la lista è vuota
void heapify (pr_heap* h);
int pr_ispresent(pr_heap* h, void* data, PREqualsFunction equals);