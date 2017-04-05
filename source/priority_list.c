#include <priority_list.h>

void pr_push (pr_heap *h, long int priority, void* data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (pr_node *)realloc(h->nodes, h->size * sizeof (pr_node));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}
 
void* pr_pop (pr_heap *h) {
    if (!h->len) {
        return NULL;
    }
    void* data = h->nodes[1].data;
    h->nodes[1] = h->nodes[h->len];
    h->len--;
    heapify(h);
    return data;
}

void heapify (pr_heap* h){
    long int j = 0;
    long int k = 0;
    long int i = 1;
    while(1) {
        k = i;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    h->nodes[i] = h->nodes[h->len + 1];
}


//restituisce TRUE se la lista è vuota
int pr_empty(pr_heap* h){
    if (h == NULL)
        return 0;
    else 
        return h->len == 0;
}

int pr_ispresent(pr_heap* h, void* data, PREqualsFunction equals){
    int find = 0;
    if (h != NULL && data != NULL){
        for(int i = 1; i <h->len && !find; i++){
            if (equals(data,h->nodes[i].data))
                find = 1;
        }
    }
    return find;
}