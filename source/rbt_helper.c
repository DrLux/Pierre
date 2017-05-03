#include "rbt_helper.h"
struct Node* outsider;

int compare_node(void* node1, void* node2, RBTCompFunction compare){
  if (node1 == get_sentinel() && node2 == get_sentinel())
    return 0;
  if (node1 == get_sentinel())
    return -1;
  if (node2 == get_sentinel())
    return 1;

  return compare(get_key(node1), get_key(node2));
}

int compare_key_with_node(void* key, void*node, RBTCompFunction compare){
  return compare(key, get_key(node));
}

void set_root(void* tree, void* node){
  (*((struct Tree*)tree)).root = (struct Node*)node;
}

void* get_sentinel(void* tree){
  return outsider;
}

void* get_parent(void* node){
  if (node != outsider)
    return (*((struct Node*)node)).parent;
  else
    return outsider;
}

void set_parent(void* node1, void* node2){
  if (node1 != outsider){
    if (node2 != outsider)
      (*((struct Node*)node1)).parent = (struct Node*)node2;
    else
      (*((struct Node*)node1)).parent = outsider;
  }
}

void* get_left(void* node){
  if (node != outsider)
    return (*((struct Node*)node)).left;
  else
    return outsider;
}

void set_left(void* node1, void* node2){
  if (node2 != outsider){
    (*((struct Node*)node1)).left = (struct Node*)node2;
    (*((struct Node*)node2)).parent = (struct Node*)node1;
  } else
    (*((struct Node*)node1)).left = outsider;
}

void* get_right(void* node){
  if (node != outsider)
    return (*((struct Node*)node)).right;
  else
    return outsider;
}

void set_right(void* node1,void* node2){
  if (node2 != outsider){  
    (*((struct Node*)node1)).right = (struct Node*)node2;
    (*((struct Node*)node2)).parent = (struct Node*)node1;
  } else
    (*((struct Node*)node1)).right = outsider;
}

void* get_key(void* node){
  if (node != outsider)
    return (*((struct Node*)node)).key;
  else
    return outsider;
}

void set_key(void* node, void* key){
  (*((struct Node*)node)).key =  (int*)key;
}

void* get_value(void* node){
  if (node != outsider)
    return (*((struct Node*)node)).value;
  else
    return NULL;
}

void set_value(void* node, void* value){
  (*((struct Node*)node)).value =  (struct Records*)value;
}

void print_key(void* node, const char* msg){
  if (node == outsider)
    printf("\nKey Inesistente (Sentinella)");
  else
    printf("%s: %d \n", msg, *(int*)get_key(node));
}

void make_tree(struct Tree* t){
  struct Node* outsider = new_node(BLACK,outsider, outsider);
  (*outsider).color = BLACK;
  (*t).root = NULL;
}

void* get_root(void* tree){
  if (tree == NULL)
    return NULL;
  if ((*((struct Tree*)tree)).root == NULL)
    return outsider;
  else 
    return (*((struct Tree*)tree)).root;
}

struct Node* new_node(int color, void* key, void* value){
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));;
  set_color((void*)new_node,color);
  set_key((void*)new_node,key);
  set_value((void*)new_node,value);
  set_left((void*)new_node, outsider);
  set_right((void*)new_node, outsider);
  set_parent((void*)new_node, outsider);
  return new_node;
}

void print_node(void* node){
  if (node == outsider)
    printf("\nNodo Sentinella");
  else{  
    if (get_parent(node) == outsider)
      print_key(node,"Key Nodo ROOT");
    else if (is_leaf(node))
          print_key(node,"Key Nodo FOGLIA");
        else
          print_key(node,"Key Nodo INTERNO");

    printf(" - Color: %d", get_color(node));
    if (get_value(node) != NULL)
      print_value(node);
    if (get_parent(node) != outsider) 
      print_key(get_parent(node)," - Parent");
    if (get_left(node) != outsider)
      print_key(get_left(node)," - Left");
    if (get_right(node) != outsider)
      print_key(get_right(node)," - Right");
  }
  puts("\n");
}

void print_value(void* node){
  //struct Records* record = (struct Records*) malloc (sizeof(struct Records));
  //*record = *(struct Records*)get_value(node);
  //printf("\n - Valore nodo: %d,%s,%d,%4.5f\n", (*record).id, (*record).string_field, (*record).numb_field, (*record).float_field);
  //free((void*)record);
}


int is_leaf(void* node){
  if ((get_right(node) == outsider && get_left(node) == outsider)) 
    return 1;
  return 0;
} 

int is_root(void* node, void* tree){
  if (node == get_root(tree)) 
    return 1;
  return 0;
} 

void clean_node (void* node){
  if (node != outsider)
    free(node);
}


void replace_node(void* node1, void* node2){
  set_left(node1,get_left(node2));
  set_right(node1,get_right(node2));
  clean_node(node2);
}

int get_color(void* node){  
  if (node == outsider)
    return BLACK;
  return (*((struct Node*)node)).color;
}

void set_color(void* node, int color){
  if (node != outsider)
    (*((struct Node*)node)).color = color;
}

