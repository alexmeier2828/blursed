#include <stdlib>
#include "linkedlist.h"

// Private functions
//TODO implement this
Link* link_at(int i);

/* 
 * alocate empty linked list
 */
LList* new_ll(){
	LList* list;
	list = malloc(sizeof(list));
	list->size = 0;
	list->head = NULL;
	return list;
}

/*
 * dealocate whole list
 */
void free_ll(LList** pp_list, Action free_item){
	int i;
	Link* link;
	Link* next;

	link = (*pp_list)->head;

	while(link != NULL){
		free_item(link->p_e);
		next = link->next;
		free(link);
		link = next;
	}

	*pp_list = NULL;
}

/*
 * push to the end of list
 */
void ll_push(LList* p_list, void* item){
	Link* new_link;
	Link* tail; 

	//TODO handle bad malloc calls
	new_link = malloc(sizeof(Link));
	new_link->p_e = item;

	if(p_list->head != null){
		tail = p_list->p_next;
		while(tail->p_next != null){
			tail = tail->p_next;
		}

		tail->p_next = new_link;
	} else {
		p_list->head = new_link;
	}
}

/* 
 * Insert item at index 
 * */
void ll_ins(LList* p_list, int i, void* item){
	int ittr;
	Link* new_link;
	Link* insert_link;

	//TODO handle bad malloc calls
	new_link = malloc(sizeof(Link));
	new_link->p_e = item;

	if(i < p_list->size && i > 0){
		insert_link = p_list->p_next;

		for(ittr = 0; ittr < i; ittr++){
			insert_link = insert_link->p_next;
		}

		new_link->p_next = insert_link->p_next;
		insert_link->p_next = new_link;
	} else if(i == 0){
		new_link->p_next = p_list->head;
		p_list->head = new_link;
	} else {
		printf("ERROR index out of bounds");
		exit(1);
	}
}

/*
 * returns item at index;
 */
void* ll_get(LList* p_list, int i);
/*
 * remove item at index
 */
void* ll_del(LList* p_list, int i);

/*
 * remove item at the end of list
 */
void* ll_pop(LList* p_list);
