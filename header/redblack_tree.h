#include "rbt_helper.h"

/*
 * Inserisce un nodo all' interno dell' albero
 * T: albero in cui inserire
 * new_node: nodo da inserire
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */
void insert(void* T, void* new_node, RBTCompFunction compare);

/*
 * Ripristina le proprietà chiave del RBT, distorte dall' inserimento
 * T: albero in cui inserire
 * new_node: nodo da inserire
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */
void insert_fixup(void* T, void* new_node, RBTCompFunction compare);

/*
 * Esegue una rotazione a sinistra del nodo passato
 * T: albero in cui inserire
 * x: nodo da inserire
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */
void left_rotate(void* T, void* x, RBTCompFunction compare);

/*
 * Esegue una rotazione a destra del nodo passato
 * T: albero in cui inserire
 * x: nodo da inserire
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */
void right_rotate(void* T, void* x, RBTCompFunction compare);

//Stampa inorder dell' albero
void inorder_print_tree(void* node);

/*
 * Ricerca di un nodo in modo iterativo
 * node: nodo da cui far partire la ricerca
 * key: valore da cercare
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */
void* iterative_tree_search(void* node, void* key, RBTCompFunction compare);

/*
 * Ricerca del nodo minimo
 * node: nodo da cui far partire la ricerca
 */
void* tree_min(void* node);

/*
 * Ricerca del nodo massimo
 * node: nodo da cui far partire la ricerca
 */
void* tree_max(void* node);

/*
 * Ricerca del nodo successore al nodo dato
 * node: nodo da cui far partire la ricerca
 */
void* tree_successor(void* node);

/*
 * Sostituisce il nodo U von il nodo V
 * T: albero
 * u: nodo da sostituire
 * v: nodo sostitutore
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */void transplant(void* T, void* u, void* v, RBTCompFunction compare);

/*
 * Elimina dall' albero il nodo selezionato
 * T: albero
 * node: nodo da eliminare
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */
void tree_delete(void* T, void* target_node, RBTCompFunction compare);

/*
 * Ripristina le proprietà chiave del RBT, distorte dall' eliminazione
 * T: albero
 * node: nodo da eliminare
 * compare: funzione per valutare l'ordine di due elementi dell'array
 */
void delete_fixup(void* T, void* target_node, RBTCompFunction compare);


void insert_bt(struct Tree* T, void* key, void* value, RBTCompFunction compare);
void* search_bt(struct Tree* T, void* key, RBTCompFunction compare);
void delete_bt(struct Tree* T, void* key, RBTCompFunction compare);

//Verifica che le proprità dell' albero R-N siano sempre rispettate
void check_rbt_prop(void* tree, void* node);

// Svuota l' albero
void clean_tree(void* tree, RBTCompFunction compare);
