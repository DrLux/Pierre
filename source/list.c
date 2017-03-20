#include "list.h"

List* new_list(){
	List* new_list = NULL;
	new_list = (List*)malloc(sizeof(List));
	new_list->sentinel = create_node(NULL);
	new_list->size = 0;
	return new_list;
}

List_Node* create_node(void* ptr){
	List_Node* new_node = NULL;
	new_node = (List_Node*)malloc(sizeof(List_Node));
	new_node->cargo = ptr;
	new_node->next = NULL;
	return new_node;
}

//Inserisci in testa
void push(List* list,void* ptr){
	if (list != NULL){
		List_Node* new_node = create_node(ptr); 
		new_node->next = list->sentinel->next;
		list->sentinel->next = new_node;
	    list->size +=1;
	}
}

//rimuove in testa
void* pop_lifo(List* list){
	void* ret_cargo = NULL;
	
	if (list != NULL){
		List_Node* temp_node = list->sentinel->next;
		if (temp_node != NULL){
			list->sentinel->next = temp_node->next; 
			ret_cargo = temp_node->cargo;
			free(temp_node);
		    list->size -=1;
		}
	}  		
	return ret_cargo;
}

//rimuove in coda
void* pop_fifo(List* list){
	void* ret_cargo = NULL;
	
	if (list != NULL){
		List_Node* current = list->sentinel;
		if (current->next != NULL){
			while (current->next->next != NULL)
				current = current->next; 
			ret_cargo = current->next->cargo;
			free(current->next);
			list->size -=1;
			current->next = NULL;
		}
	}	  		
	return ret_cargo;
}

//restituisce TRUE se la lista è vuota
int empty(List* list){
	if (list != NULL)
		return list->sentinel->next == NULL;
	else
		return list == NULL;
}

int size(List* list){
	if (list != NULL)
		return list->size;
	else
		return list == NULL;
}

void clean_list(List* list){
	if (list != NULL){
		List_Node* current = NULL;
		while (list->sentinel->next != NULL){
			current = list->sentinel->next;
			list->sentinel->next = current->next;
			free(current);
			list->size -=1;
		}
	}
}



//Sistemare la calloc
//Finire i test
int main() {
    //List* list = NULL;
    //list = new_list();

    printf("Test lista NULL\n");
    push(NULL, NULL);
    pop_lifo(NULL);
    pop_fifo(NULL);
    empty(NULL);
    size(NULL);
    clean_list(NULL);

    return 0;
}

