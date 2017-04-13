#include <stdlib.h>
#include <stdio.h>

typedef struct {
	void** queue;
	size_t inserted;
	size_t size;
} heap_list, *Pr_List;

//torna 0 se i due elementi (probabilmete stati) sono uguali, 1 se il primo è maggiore, -1 altrimenti
typedef int (*PRCompFunction)(void*, void*);

Pr_List new_pr_list();
void pr_insert(Pr_List pq, void* element);
void sift_down(void** array, int root, int end, PRCompFunction compare);
void min_heapify(void** array, size_t inserted, PRCompFunction compare);
void* pr_pop_min(Pr_List pq, PRCompFunction compare);
void pr_destroy(Pr_List pq);

