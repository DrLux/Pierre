#include <stdlib.h>
#include <stdio.h>

typedef struct {
	void** queue;
	size_t inserted;
	size_t size;
} Pr_List, *heap_list;

//torna 0 se i due elementi (probabilmete stati) sono uguali, 1 se il primo è maggiore, -1 altrimenti
typedef int (*PRCompFunction)(void*, void*);

heap_list new_pr_list();
void pr_insert(heap_list pq, void* element);
void sift_down(void** array, int root, int end, PRCompFunction compare);
void min_heapify(void** array, size_t inserted, PRCompFunction compare);
void* pr_pop_min(heap_list pq, PRCompFunction compare);
void pr_destroy(heap_list pq);
int pr_empty(heap_list pq);
void* pr_isPresent(heap_list pq, void* elem,PRCompFunction compare);
