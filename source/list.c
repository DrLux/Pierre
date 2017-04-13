#include "list.h"

List* new_list(){
	List* new_list = (List*)calloc(1,sizeof(List));
	new_list->sentinel = create_node(NULL);
	new_list->size = 0;
	return new_list;
}

List_Node* create_node(void* ptr){
	List_Node* new_node = (List_Node*)calloc(1,sizeof(List_Node));
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
	if (!empty(list)){
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
	
	if (!empty(list)){
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
	if (list != NULL){
		return list->sentinel->next == NULL;
	}
	else
		return list == NULL;
}

int size(List* list){
	if (list != NULL)
		return list->size;
	else
		return -1;
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
	free(list);
	}
}

//torna 1 quando c'è
int is_present(List* list, void* ptr, EqualsFunction equals){
	int ret = 0;
	if (list != NULL){
		List_Node* iterator = list->sentinel->next;
		while (iterator != NULL && ret == 0){
			ret = !(equals(ptr, iterator->cargo) == 0);
			iterator = iterator->next;
		}
	}
	return ret;
}