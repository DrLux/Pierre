#include "redblack_tree.h"

void insert_bt(struct Tree* T, void* key, void* value, RBTCompFunction compare){
  struct Node* node = new_node(BLACK, key, value);
  insert((void*)T, (void*)node, compare);
}

void* search_bt(struct Tree* T, void* key, RBTCompFunction compare){
  struct Node* node = NULL;
  node = (struct Node*)(iterative_tree_search( get_root((void*)T), key, compare));
  return get_value(node);
}

void delete_bt(struct Tree* T, void* key, RBTCompFunction compare){
	struct Node* node = NULL;
 	node = iterative_tree_search( get_root((void*)T), key, compare);
	tree_delete((void*)T, node,compare);
}


void insert(void* T, void* new_node, RBTCompFunction compare) {
	void* y = get_sentinel();
	void* x = get_root(T);

	while ( x != get_sentinel()){
		y = x;
		if (compare_node(new_node,x,compare) == 0){
			y = get_parent(x);
			replace_node(new_node,x);
			x = get_sentinel();
		} else if (compare_node(new_node,x,compare) < 0)
			x = get_left(x);
				else
					x = get_right(x);
	}
	set_parent(new_node,y);
	if ( y == get_sentinel())
		set_root(T,new_node);
	else if (compare_node(new_node,y,compare) < 0)
			set_left(y,new_node);
		else
			set_right(y,new_node);
	set_left(new_node,get_sentinel());
	set_right(new_node,get_sentinel());
	set_color(new_node,RED);

	insert_fixup(T,new_node,compare);
}


void insert_fixup(void* T, void* new_node, RBTCompFunction compare) {
	void* y = get_sentinel();

	while(get_color(get_parent(new_node)) == RED ){
		if (compare_node(get_parent(new_node),get_left(get_parent(get_parent(new_node))),compare) == 0) {
			y = get_right(get_parent(get_parent(new_node)));
			if (get_color(y) == RED){
				set_color(get_parent(new_node),BLACK);
				set_color(y,BLACK);
				set_color(get_parent(get_parent(new_node)),RED);
				new_node = get_parent(get_parent(new_node));
			} else {
				if(compare_node(new_node,get_right(get_parent(new_node)),compare) == 0){
						new_node = get_parent(new_node);
						left_rotate(T,new_node,compare);
			}
			
			set_color(get_parent(new_node), BLACK);
			set_color(get_parent(get_parent(new_node)), RED);
			right_rotate(T,get_parent(get_parent(new_node)),compare);
			}
		} else {			
			y = get_left(get_parent(get_parent(new_node)));
			if (get_color(y) == RED){
				set_color(get_parent(new_node),BLACK);
				set_color(y,BLACK);
				set_color(get_parent(get_parent(new_node)),RED);
				new_node = get_parent(get_parent(new_node));
			} else {
				if(compare_node(new_node,get_left(get_parent(new_node)),compare) == 0){
						new_node = get_parent(new_node);
						right_rotate(T,new_node,compare);
				}
			set_color(get_parent(new_node), BLACK);
			set_color(get_parent(get_parent(new_node)), RED);
			left_rotate(T,get_parent(get_parent(new_node)),compare);
			}
		}
	}
	set_color(get_root(T), BLACK);	
}

void left_rotate(void* T, void* x, RBTCompFunction compare) {
	void* y = get_right(x);
	set_right(x,get_left(y));																			
	if (get_left(y) != get_sentinel())
		set_parent(get_left(y),x);
	set_parent(y,get_parent(x));
	if(get_parent(x) == get_sentinel())
		set_root(T,y);
	else if(x == get_left(get_parent(x)))
			set_left(get_parent(x), y);
		else set_right(get_parent(x),y);
	set_left(y,x);
	set_parent(x,y);	
}	

void right_rotate(void* T, void* x, RBTCompFunction compare) {
	void* y = get_left(x);
	set_left(x,get_right(y));
	if (get_right(y) != get_sentinel())
		set_parent(get_right(y),x);
	set_parent(y,get_parent(x));
	if(get_parent(x) == get_sentinel())
		set_root(T,y);
	else if(x == get_right(get_parent(x)))
			set_right(get_parent(x), y);
		else set_left(get_parent(x),y);
	set_right(y,x);
	set_parent(x,y);
}	

void inorder_print_tree(void* node) {
	if (node != get_sentinel()){
		inorder_print_tree(get_left(node));
		print_node(node);
		inorder_print_tree(get_right(node));
	}
}

void* iterative_tree_search(void* node, void* key, RBTCompFunction compare){
	while (node != get_sentinel() && (compare_key_with_node(key,node,compare) < 0 || (compare_key_with_node(key,node,compare) > 0))){
		if (compare_key_with_node(key,node,compare) < 0)
			node = get_left(node);
		else
			node = get_right(node);
	}
	return node;
}

void* tree_min(void* node){
	while (get_left(node) != get_sentinel())
		node = get_left(node);
	return node;
}

void* tree_max(void* node){
	while (get_right(node) != get_sentinel())
		node = get_right(node);
	return node;
}


void transplant(void* T, void* u, void* v, RBTCompFunction compare){
	if (get_parent(u) == get_sentinel())
		set_root(T,v);
	else 
		if (u == get_left(get_parent(u)))
			set_left(get_parent(u),v);
		else 
			set_right(get_parent(u),v);
	set_parent(v,get_parent(u));
}

void tree_delete(void* T, void* target_node, RBTCompFunction compare){
	void* y;
	void* x;
	int y_original_color;

	y = target_node;
	y_original_color = get_color(y);
	
	if (get_left(target_node) == get_sentinel()) {      
		x = get_right(target_node);
		transplant(T,target_node,x,compare);
	} else {
		if (get_right(target_node) == get_sentinel()) {
		x = get_left(target_node);
		transplant(T,target_node,x,compare);            
		} else {
			y = tree_min(get_right(target_node));
			y_original_color = get_color(y);
			x = get_right(y);
			if (get_parent(y) == target_node){
				set_parent(x,y);
			} else {
				transplant(T,y,x,compare);
				set_right(y, get_right(target_node));
				set_parent(get_right(y), y);
			}
			transplant(T,target_node,y,compare);
			set_left(y,get_left(target_node));
			set_parent(get_left(y), y);
			if (get_color(target_node) == BLACK)
				set_color(y,BLACK);
			else
				set_color(y,RED);
		}
	}
	if (y_original_color == BLACK)
		delete_fixup(T,x,compare);
	clean_node(target_node);
}

void delete_fixup(void* T, void* x, RBTCompFunction compare){
	void* w;
	while( x != get_root(T) && get_color(x) == BLACK && x != get_sentinel()){
		if (x == get_left(get_parent(x))){
			w = get_right(get_parent(x));
			if (get_color(w) == RED){
				set_color(w,BLACK);
				set_color(get_parent(x),RED);
				left_rotate(T,get_parent(x),compare);
				w = get_right(get_parent(x));
			}
			if (get_color(get_left(w)) == BLACK && get_color(get_right(w)) == BLACK){
				set_color((w),RED);
				x = get_parent(x);
			} else {
					if (get_color(get_right(w)) == BLACK){
						set_color(get_left(w),BLACK);
						set_color(w,RED);
						right_rotate(T,w,compare);
						w = get_right(get_parent(x));
					}
			set_color(w,get_color(get_parent(x)));
			set_color(get_parent(x), BLACK);
			set_color(get_right(w), BLACK);
			left_rotate(T,get_parent(x),compare);
			x = get_root(T);
			}
		} else {
			w = get_left(get_parent(x));
			if (get_color(w) == RED){
				set_color(w,BLACK);
				set_color(get_parent(x),RED);
				right_rotate(T,get_parent(x),compare);
				w = get_left(get_parent(x));
			}
			if (get_color(get_right(w)) == BLACK && get_color(get_left(w)) == BLACK){
				set_color((w),RED);
				x = get_parent(x);
			} else {
				if (get_color(get_left(w)) == BLACK){
					set_color(get_right(w),BLACK);
					set_color(w,RED);
					left_rotate(T,w,compare);
					w = get_left(get_parent(x));
				}
			set_color(w,get_color(get_parent(x)));
			set_color(get_parent(x), BLACK);
			set_color(get_left(w), BLACK);
			right_rotate(T,get_parent(x),compare);
			x = get_root(T);
			}
		}
	}
	set_color(x, BLACK);
}


void clean_tree(void* tree, RBTCompFunction compare){ 
  struct Node* min_max = NULL;
  struct Node* root = NULL;

  root = get_root(tree);  
  while(tree_min(root) != root || tree_max(root) != root){
    min_max = tree_min(root);
    if (min_max == root)
      min_max = tree_max(root);
    tree_delete(tree, min_max, compare);    
    check_rbt_prop(tree,get_sentinel());
  }
  //clean_node(root);  
  set_root(tree,NULL);
}

void check_rbt_prop(void* tree, void* node){
  assert(get_color(get_root(tree)) == BLACK); 
  assert(get_color(get_sentinel()) == BLACK); 
  if (node != get_sentinel()){
    check_rbt_prop(tree,get_left(node));
    check_rbt_prop(tree,get_right(node));
  }
}