#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define RED 0
#define BLACK 1

/*
 * Struct che rappresenta un nodo dell' albero
 * key: campo con cui si effettuano i confronti tra nodi
 * value: riga del file connessa al nodo
 * key_type: definisce se il confronto è fatto su int,float o string
 * color: colore del nodo che puo essere Nero o Rosso
 * left: figlio sinistro
 * parent: nodo padre
 * right: figlio destro
 */
struct Node{
	void* key;
	void* value;
	short int color;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};

//Nodo sentinella usato per tutte le foglie
extern struct Node* outsider;


//Struct che rappresente l' albero BST
struct Tree {
  	struct Node* root;  
};

/*
 * Definizione un puntatore a funzione
 * Funzione di confronto tra due elementi dell'array
 * I paramentri sono 2 puntatori a void
 * Il return è intero e cambia in base al confronte del valore dei due parametri
 */ 
typedef int (*RBTCompFunction)(void*, void*);

// Crea l' albero rosso-nero
void make_tree(struct Tree* t);

/* 
 * Crea un nodo dell' albero
 * key_type: definisce il tipo della chiave
 * color: stabilisce il colore del nodo da creare
 * key: puntatore alla key, campo del nodo
 * value: puntatore alla riga associata al nodo
 */
struct Node* new_node(int color, void* key, void* value);

//Stampa gli attributi del nodo
void print_node(void* node);
//Stampa solo la key del nodo
void print_key(void* node, const char* msg);
//Stampa solo il value del nodo
void print_value(void* node);

//Libera le risorse occupate dal nodo
void clean_node (void* node);

//Definisce se il nodo in questione è una foglia
int is_leaf(void* node);
//Definisce se il nodo in questione è il root
int is_root(void* node, void* tree);

//Torna il puntatore al root
void* get_root(void* tree);
//Setta il nodo passato come root dell' albero
void set_root(void* tree, void* node);

//Torna il puntatore al padre del nodo passato
void* get_parent(void* node);
//Setta node2 come padre di node1
void set_parent(void* node1, void* node2);

//Torna il puntatore al figlio sinistro del nodo passato
void* get_left(void* node);
//Setta node2 come figlio sinistro di node1
void set_left(void* node1, void* node2);

//Torna il puntatore al figlio destro del nodo passato
void* get_right(void* node);
//Setta node2 come figlio destro di node1
void set_right(void* node1,void* node2);

//Torna il puntatore alla key del nodo passato
void* get_key(void* node);
//Setta key come chiave di node
void set_key(void* node, void* key);

//Torna il puntatore alla value del nodo passato
void* get_value(void* node);
//Setta value come valore di node
void set_value(void* node, void* value);

//Torna il puntatore al nodo outsider
void* get_sentinel();


//Torna il colore del nodo passato
int get_color(void* node);
//Setta il colore di node
void set_color(void*node, int color);

/*
 * Compara 2 key
 *	ptr1: puntatore alla prima key
 *	ptr2: puntatore alla seconda key
 */
int compare_node(void* ptr1, void* ptr2, RBTCompFunction compare);


int compare_key_with_node(void* key, void*node, RBTCompFunction compare);

//Elimina node2 e lo rimpiazza con node1
void replace_node(void* node1, void* node2);

