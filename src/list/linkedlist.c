#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

// Macros
#define safe_index(x, ub) (x >= 0 && x < ub)

// Private functions
Link* link_at(Link* head, int i);

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
		next = link->p_next;
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

	new_link = malloc(sizeof(Link));
	if(new_link == NULL){
		printf("ERROR: LinkedList: Malloc failure");
	}
	new_link->p_e = item;

	if(p_list->head != NULL){
		tail = p_list->head;
		while(tail->p_next != NULL){
			tail = tail->p_next;
		}

		tail->p_next = new_link;
	} else {
		p_list->head = new_link;
	}

	p_list->size++;
}

/* 
 * Insert item at index 
 * */
void ll_ins(LList* p_list, int i, void* item){
	int ittr;
	Link* new_link;
	Link* insert_link;

	new_link = malloc(sizeof(Link));
	if(new_link == NULL){
		printf("ERROR: LinkedList: Malloc failure");
	}
	new_link->p_e = item;

	if(i <= p_list->size && i > 0){
		insert_link = link_at(p_list->head, i - 1);
		new_link->p_next = insert_link->p_next;
		insert_link->p_next = new_link;
	} else if(i == 0){
		new_link->p_next = p_list->head;
		p_list->head = new_link;
	} else {
		printf("ERROR index out of bounds\n");
		printf("ll->size: %d\nindex   : %d", p_list->size, i);
		exit(1);
	}

	p_list->size++;
}

/*
 * returns item at index;
 */
void* ll_get(LList* p_list, int i){
	Link* target;

	if(!safe_index(i, p_list->size)){
		printf("ERROR index out of bounds");
		exit(1);
	}

	target = link_at(p_list->head, i);

	return target->p_e;
}
/*
 * remove item at index
 */
void* ll_del(LList* p_list, int i){
	Link* left; 
	Link* temp;
	void* item; 

	if(!safe_index(i, p_list->size)){
		printf("ERROR index out of bounds");
		exit(1);
	}

	left = link_at(p_list->head, i - 1);
	temp = left->p_next;
	left->p_next = temp->p_next;
	item = temp->p_e;
	free(temp);

	p_list->size--;
	return item;
}

/*
 * remove item at the end of list
 */
void* ll_pop(LList* p_list){
	Link* new_tail;
	Link* old_tail;
	void* item;

	if(p_list->size <= 0){
		printf("ERROR called pop on empty list");
		exit(1);
	}

	if(p_list->size >= 1){			
		new_tail = link_at(p_list->head, p_list->size - 2);
		old_tail = new_tail->p_next;
		new_tail->p_next = NULL;
	} else {
		old_tail = p_list->head;
		p_list->head = NULL;
	}
	
	item = old_tail->p_e;
	free(old_tail);
	p_list->size--;
	return item;
}


// Private functions

/*
 * gets link at index
 */
Link* link_at(Link* head ,int index){
	Link* target;
	int i;
	
	target = head;
	for(i = 0; i < index; i++){
		target = target->p_next;	
	}

	return target; 
}


