#include <priority_list.h>

#define PARENT(i) ((i)-1)/2
#define LEFT_CHILD(i) (2*(i))+1

void swappa(void** e1, void** e2) {
  void* tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}

//la grandezza di default è 1
heap_list new_pr_list() {
    heap_list newpq = (heap_list) calloc(1,sizeof(Pr_List));
    newpq->queue = (void**) calloc(1,sizeof(void*));
    newpq->inserted = 0;
    newpq->size = 1;
    return newpq;
}


void pr_destroy(heap_list pq) {
    if (pq) {
    free(pq->queue);
    free(pq);
  }
}

//ritornare direttamente la condizione dell' if
int pr_empty(heap_list pq){
  if (pq == NULL || pq->inserted == 0 || pq->size == 0 || pq->queue == NULL)
    return 1;
  else
    return 0;
}

//la lista si riadatta automaticamente
void pr_insert(heap_list pq, void* element) {
    if (pq->inserted == pq->size) {
        pq->size = pq->size*2;
        pq->queue = (void**)realloc(pq->queue, pq->size * sizeof(void*));
    }
    pq->queue[pq->inserted] = element;
    pq->inserted++;
}


void sift_down(void** array, int root, int end, PRCompFunction compare) {
  int child = LEFT_CHILD(root),
      swp = root;

  while(child <= end) {

    if (compare(array[swp], array[child]) > 0)
      swp = child;

    if (child+1 <= end && compare(array[swp], array[child+1]) > 0)
      swp = child + 1;

    if (swp != root) {
      swappa(&array[root], &array[swp]);
      root = swp;
    } else
      break;

    child = LEFT_CHILD(root);
  }

}


void min_heapify(void** array, size_t inserted, PRCompFunction compare) {
  if (inserted > 1){
    for (int i = PARENT((int)inserted - 1); i >= 0; i--)
      sift_down(array, i, inserted - 1, compare);
  }
}

//estrae il primo elemento della lista
void* pr_pop_min(heap_list pq, PRCompFunction compare) {
    if (pq->inserted > 0){
    min_heapify(pq->queue, pq->inserted, compare);
    void* min = pq->queue[0];
    pq->queue[0] = pq->queue[pq->inserted-1];
    pq->inserted--;
    return min;
  } else
        return NULL;
}

/*
per debug
int ciao(void* ptr1, void* ptr2) {
    int i1 =  *((int*)ptr1);
    int i2 =  *((int*)ptr2);

    if (i1 < i2) return -1;
    if (i1 == i2) return 0;

    return 1;
}

void print_queue(heap_list pq) {
    for (int i = 0; i < pq->inserted; i++)
      printf("Il nodo ad indice %d vale: %d\n", i,*((int*)pq->queue[i]));
}
*/

//torna null se l' elemento non è presente
void* pr_isPresent(heap_list pq, void* elem,PRCompFunction compare) {
    for (int i = 0; i < pq->inserted; i++){
      if (compare(pq->queue[i], elem) == 0)
        return pq->queue[i];
    }
    return NULL;
}
/*
int main(){
    //testare la pop
    Pr_List* Open = new_heap_list();
    int* x = 0;

    int a = 1;
    int e = 5;
    int b = 2;
    int c = 3;
    int d = 4;

    int* temp = NULL;

    pr_insert(Open,(void*)&a);
    pr_insert(Open,(void*)&c);
    pr_insert(Open,(void*)&b);
    pr_insert(Open,(void*)&e);
    pr_insert(Open,(void*)&d);

    x = pr_isPresent(Open, (void*)&a, &ciao);
    *x = 19;

    temp = (int*)pr_pop_min(Open, &ciao);
    while (temp != NULL){
        printf("Estratto: %d\n", *temp);
        temp = (int*)pr_pop_min(Open, &ciao);
    }

    return 0;
}*/


